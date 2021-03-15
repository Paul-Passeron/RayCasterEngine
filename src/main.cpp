#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <list>
#include "RenderWindow.hpp"
#include "entity.hpp"
#include "geometry.hpp"
#include <cmath>
#include <chrono>
int main(int arc, char* args[]){
	if(SDL_Init(SDL_INIT_VIDEO) > 0){
		std::cout << "SDL has failed: "<<SDL_GetError()<<std::endl;
	}
	if(!IMG_Init(IMG_INIT_PNG)){
		std::cout << "IMG has failed: "<<SDL_GetError()<<std::endl;
	}
	const int nScreenWidth = 800;
	const int nScreenHeight = 800;
	RenderWindow window("Game v1.0", nScreenWidth, nScreenHeight);

	//Variables of the game 
	
	float PI = 3.14156;
	float fFOV = PI/3.0f;
	float fPlayerX = 8.0f;
	float fPlayerY = 6.0f;
	float fPlayerA = PI;
	int nTextureHeight = 32;
	int nTextureNumber = 4;
	float fLastElapsed = 0;
	std::vector<line> linelist = {
		{ 12.8f, 30.08f, 13.8666666667f, 21.3333333333f,1 },

		{ 13.8666666667f, 21.3333333333f, 18.0266666667f, 18.3466666667f,1 },

		{ 18.0266666667f, 18.3466666667f, 26.1333333333f, 20.48f,1 },

		{ 26.1333333333f, 20.48f, 27.52f, 26.56f,1 },

		{ 27.52f, 26.56f, 26.9866666667f, 33.28f,1 },

		{ 26.9866666667f, 33.28f, 40.0f, 39.4666666667f,1 },

		{ 40.0f, 39.4666666667f, 44.0533333333f, 42.4533333333f,1 },

		{ 44.0533333333f, 42.4533333333f, 38.9333333333f, 49.28f,1 },

		{ 38.9333333333f, 49.28f, 31.68f, 46.4f,1 },

		{ 31.68f, 46.4f, 23.2533333333f, 39.8933333333f,1 },

		{ 23.2533333333f, 39.8933333333f, 15.4666666667f, 40.32f,1 },

		{ 15.4666666667f, 40.32f, 11.9466666667f, 44.3733333333f,1 },

		{ 11.9466666667f, 44.3733333333f, 5.12f, 32.5333333333f,1 },

		{ 5.12f, 32.5333333333f, 3.73333333333f, 22.1866666667f,1 },

		{ 3.73333333333f, 22.1866666667f, 6.18666666667f, 18.4533333333f,1 },

		{ 6.18666666667f, 18.4533333333f, 8.0f, 21.12f,1 },

		{ 8.0f, 21.12f, 8.64f, 27.52f,1 },

		{ 8.64f, 27.52f, 10.56f, 30.6133333333f,2 },

		{ 10.56f, 30.6133333333f, 13.5466666667f, 34.3466666667f,2 },

		{ 13.5466666667f, 34.3466666667f, 15.2533333333f, 31.2533333333f,2 },

		{ 15.2533333333f, 31.2533333333f, 16.96f, 29.2266666667f,2 },

		{ 16.96f, 29.2266666667f, 18.88f, 28.0533333333f,3 },

		{ 18.88f, 28.0533333333f, 21.0133333333f, 22.9333333333f,3 },

		{ 21.0133333333f, 22.9333333333f, 21.6533333333f, 32.5333333333f,3 },

		{ 21.6533333333f, 32.5333333333f, 22.2933333333f, 31.8933333333f,3 },

		{ 22.2933333333f, 31.8933333333f, 23.5733333333f, 29.2266666667f,3 },

		{ 23.5733333333f, 29.2266666667f, 23.1466666667f, 25.0666666667f,3 },

		{ 23.1466666667f, 25.0666666667f, 22.08f, 22.8266666667f,3 },

		{ 22.08f, 22.8266666667f, 21.2266666667f, 21.76f,3 },

		{ 21.2266666667f, 21.76f, 18.1333333333f, 22.72f,3 },

		{ 18.1333333333f, 22.72f, 16.4266666667f, 24.5333333333f,3 },

		{ 16.4266666667f, 24.5333333333f, 16.0f, 26.0266666667f,3 },

		{ 16.0f, 26.0266666667f, 15.68f, 28.6933333333f,3 },

		{ 15.68f, 28.6933333333f, 13.8666666667f, 29.5466666667f,3 },

		{ 13.8666666667f, 29.5466666667f, 11.84f, 26.4533333333f,2 },};
	std::chrono::time_point<std::chrono::system_clock> m_tp1, m_tp2;
	m_tp1 = std::chrono::system_clock::now();
	m_tp2 = std::chrono::system_clock::now();

	SDL_Texture* textureAtlas = window.loadTexture("res/gfx/textureAtlas.png");
	std::vector<Entity> entities(nScreenWidth, Entity(0,0,textureAtlas,1,1,0.5));
	bool gameRunning = true;
  	SDL_Event event;
	while(gameRunning){
		m_tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = m_tp2 - m_tp1;
		m_tp1 = m_tp2;

		// Our time per frame coefficient
		float fElapsedTime = elapsedTime.count();
		fLastElapsed = fElapsedTime;
		std::cout<<"FPS: "<<1.0f/fElapsedTime<<std::endl;
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					gameRunning = false;
					break;
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_a)
							fPlayerA -=fElapsedTime*10.0f;
					if(event.key.keysym.sym == SDLK_e)
							fPlayerA +=fElapsedTime*10.0f;
						
						if(event.key.keysym.sym == SDLK_z){
							fPlayerX += sinf(fPlayerA)*fElapsedTime*100.0f;
							fPlayerY += cosf(fPlayerA)*fElapsedTime*100.0f;
						}
						if(event.key.keysym.sym == SDLK_s){
							fPlayerX -= sinf(fPlayerA)*fElapsedTime*100.0f;
							fPlayerY -= cosf(fPlayerA)*fElapsedTime*100.0f;
						}
						if(event.key.keysym.sym == SDLK_d){
							fPlayerX += sinf(fPlayerA)*fElapsedTime*100.0f;
							fPlayerY -= cosf(fPlayerA)*fElapsedTime*100.0f;
						}
						if(event.key.keysym.sym == SDLK_q){
							fPlayerX -= sinf(fPlayerA)*fElapsedTime*100.0f;
							fPlayerY += cosf(fPlayerA)*fElapsedTime*100.0f;
						}
					
					break;
				default:
					break;
			}
		}
		//Game Loop
		// Handle Timing
				depthElement dDepthBuffer[nScreenWidth]{1000.0f, 0.0f, 1};
		
		
		//std::cout << fPlayerA << std::endl;
		window.clear();
		point pPlayerPoint = {fPlayerX, fPlayerY};
		for(int x = 0; x<nScreenWidth; x++){
			dDepthBuffer[x].dist = 1000.0f;
			float fRayAngle = -fFOV / 2.0f + fPlayerA + fFOV * float(x) / (float)nScreenWidth;
			float fRayX = sinf(fRayAngle);
			float fRayY = cosf(fRayAngle);
			point pRayPoint = {fRayX + fPlayerX, fRayY + fPlayerY};
			line lSeeLine = {pPlayerPoint, pRayPoint};
			for(int lineIndex = 0; lineIndex < linelist.size(); lineIndex++){
				point pEyeWallIntersection = line_line_intersection(lSeeLine, linelist[lineIndex]);
				if(pEyeWallIntersection.x < 1000.0f){
					
					float distance = dist(pEyeWallIntersection, pPlayerPoint);
					//std::cout <<distance<<std::endl;
					float sample = dist(pEyeWallIntersection, linelist[lineIndex].p1);
					//float sample = 0.1f;
					sample = sample - floor(sample);
					if(distance < dDepthBuffer[x].dist && distance > 0){
						//std::cout<<"yay"<<std::endl;
						dDepthBuffer[x].dist = distance;
						dDepthBuffer[x].sample = sample;
						dDepthBuffer[x].nTextureIdentifier =  linelist[lineIndex].nTextureIdentifier;
						//std::cout<<(float)x/(float)nScreenWidth<<std::endl;
						//std::cout<<distance<<std::endl;
						//dDepthBuffer[x] = {distance, sample, linelist[lineIndex].nTextureIdentifier};
					}
				}
			}
			float fWallSize = 1.26f * (float)nScreenHeight / cosf(fPlayerA - fRayAngle)/ dDepthBuffer[x].dist;
			float fScalingFactor = fWallSize / (float)nTextureHeight;
			entities[x].setX(x);
			entities[x].setY(nScreenHeight/2.0f - fWallSize/2.0f);
			
			entities[x].setSize(fScalingFactor);
			entities[x].setIdentifier(dDepthBuffer[x].nTextureIdentifier);
			entities[x].setSample(dDepthBuffer[x].sample);
			//std::cout<<entities[x].getSample()<<std::endl;
			window.render(entities[x]);
		}
		window.display();

	}
	window.cleanUp();
	SDL_Quit();
	return 0;
}