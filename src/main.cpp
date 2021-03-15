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
#include <windows.h>
int main(int arc, char* args[]){
	HWND WindowHandle = GetConsoleWindow();
	ShowWindow(WindowHandle, SW_HIDE);
	if(SDL_Init(SDL_INIT_VIDEO) > 0){
		std::cout << "SDL has failed: "<<SDL_GetError()<<std::endl;
	}
	if(!IMG_Init(IMG_INIT_PNG)){
		std::cout << "IMG has failed: "<<SDL_GetError()<<std::endl;
	}
	const int nScreenWidth = 1920/2;
	const int nScreenHeight = 1080/2;

	
	RenderWindow window("Game v1.0", nScreenWidth, nScreenHeight);
	SDL_Surface* icon = IMG_Load("res/gfx/icon.png");
	window.setIcon(icon);
	//Variables of the game 
	
	float PI = 3.1415926535f;
	float fFOV = PI/3.0f;
	float fPlayerX = 20.0f;
	float fPlayerY = 20.0f;
	float fPlayerA = 0;
	float fLastElapsed = 0;
	float fSPEED = 10.0f;
	float fCollisionRadius = 0.1f;

	int nTextureHeight = 32;
	int nTextureNumber = 4;

	bool gameRunning = true;

	const Uint8* keyState;

	

	std::chrono::time_point<std::chrono::system_clock> m_tp1, m_tp2;
	
	SDL_Texture* ceilingTex = window.loadTexture("res/gfx/ceiling.png");
	SDL_Texture* floorTex = window.loadTexture("res/gfx/floor.png");
	SDL_Texture* textureAtlas = window.loadTexture("res/gfx/textureAtlas.png");
	SDL_Texture* hands = window.loadTexture("res/gfx/hands.png");

	SDL_Event event;

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
	std::vector<Entity> entities(nScreenWidth*2, Entity(0,0,textureAtlas,1,1,0.5));	
	
	m_tp1 = std::chrono::system_clock::now();
	m_tp2 = std::chrono::system_clock::now();
  	
  
	while(gameRunning){

		m_tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = m_tp2 - m_tp1;
		m_tp1 = m_tp2;
		float fElapsedTime = elapsedTime.count();
		fLastElapsed = fElapsedTime;
		//std::cout<<"FPS: "<<1.0f/fElapsedTime<<std::endl;
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					gameRunning = false;
					break;
				case SDL_KEYDOWN:
					break;
				default:
					break;
			}
		}
		float fNewX = 0.0f;
		float fNewY = 0.0f;
		bool bCanMoveX = true;
		bool bCanMoveY = true;
		//INPUT HANDLING
		SDL_PumpEvents();
		keyState = SDL_GetKeyboardState(NULL);
		if(keyState[SDL_SCANCODE_ESCAPE])
			gameRunning = false;
		if(keyState[SDL_SCANCODE_Q]){
			fPlayerA -= fElapsedTime*2.0f;
		}
		if(keyState[SDL_SCANCODE_E]){
			fPlayerA += fElapsedTime*2.0f;
		}
		if(keyState[SDL_SCANCODE_W]){
			fNewX += sinf(fPlayerA)*fElapsedTime*fSPEED;
			fNewY += cosf(fPlayerA)*fElapsedTime*fSPEED;
		}
		if(keyState[SDL_SCANCODE_S]){
			fNewX -= sinf(fPlayerA)*fElapsedTime*fSPEED;
			fNewY -= cosf(fPlayerA)*fElapsedTime*fSPEED;
		}
		if(keyState[SDL_SCANCODE_A]){
			fNewX -= cosf(fPlayerA)*fElapsedTime*fSPEED;
			fNewY += sinf(fPlayerA)*fElapsedTime*fSPEED;
		}
		if(keyState[SDL_SCANCODE_D]){
			fNewX += cosf(fPlayerA)*fElapsedTime*fSPEED;
			fNewY -= sinf(fPlayerA)*fElapsedTime*fSPEED;
		}
		//Game Loop
		// Handle Timing
		depthElement dDepthBuffer[nScreenWidth]{1000.0f, 0.0f, 1};
		
		window.clear();
		point pPlayerPoint = {fPlayerX, fPlayerY};
		//Draw floor and ceiling temporary;
		window.render(ceilingTex, nScreenWidth, 0, 0, 1, 1);
		window.render(floorTex, nScreenWidth, 0, nScreenHeight/2, 1, 1);
		for(int x = 0; x<nScreenWidth; x++){
			dDepthBuffer[x].dist = 1000.0f;
			float fRayAngle = -fFOV / 2.0f + fPlayerA + fFOV * float(x) / (float)nScreenWidth;
			float fRayX = sinf(fRayAngle);
			float fRayY = cosf(fRayAngle);
			point pRayPoint = {fRayX + fPlayerX, fRayY + fPlayerY};
			line lSeeLine = {pPlayerPoint, pRayPoint};
			for(int lineIndex = 0; lineIndex < linelist.size(); lineIndex++){
				point pEyeWallIntersection = line_line_intersection(lSeeLine, linelist[lineIndex]);
				if(bCanMoveX or bCanMoveY){
					point pxy = {fPlayerX+fNewX, fPlayerY+fNewY};
					point px = {fPlayerX+fNewX, fPlayerY};
					point py = {fPlayerX, fPlayerY+fNewY};

					point pRayPointxy = {fRayX + fNewX + fPlayerX, fRayY + fNewY + fPlayerY};
					point pRayPointy = {fRayX + fPlayerX, fRayY + fNewY + fPlayerY};
					point pRayPointx = {fRayX + fNewX + fPlayerX, fRayY + fPlayerY};

					point pPlayerPointxy = {fPlayerX + fNewX, fPlayerY + fNewY};
					point pPlayerPointx = {fPlayerX + fNewX, fPlayerY};
					point pPlayerPointy = {fPlayerX, fPlayerY + fNewY};

					line lxy = {pPlayerPointxy, pRayPointxy};
					line lx = {pPlayerPointx, pRayPointx};
					line ly = {pPlayerPointy, pRayPointy};

					point interxy = llinter(lxy, linelist[lineIndex]);
					point interx = llinter(lx, linelist[lineIndex]);
					point intery = llinter(ly, linelist[lineIndex]);

					float distancenxy = dist(interxy, pxy);
					float distancenx = dist(interx, px);
					float distanceny = dist(intery, py);
					
					if(distancenxy<=fCollisionRadius){
						bCanMoveY = false;
						bCanMoveX = false;
					}
					if(distancenx<=fCollisionRadius){
						bCanMoveX = false;
					}
					if(distanceny<=fCollisionRadius){
						bCanMoveY = false;
					}
				}
				if(pEyeWallIntersection.x < 1000.0f){
					
					float distance = dist(pEyeWallIntersection, pPlayerPoint);
					
					float sample = dist(pEyeWallIntersection, linelist[lineIndex].p1);
					
					sample = sample - floor(sample);
					if(distance < dDepthBuffer[x].dist && distance > 0){
						
						dDepthBuffer[x].dist = distance;
						dDepthBuffer[x].sample = sample;
						dDepthBuffer[x].nTextureIdentifier =  linelist[lineIndex].nTextureIdentifier;
						
					}
				}
			}
			
			float fWallSize = 1.26f * (float)nScreenHeight / cosf(fPlayerA - fRayAngle)/ dDepthBuffer[x].dist;
			float fWallSizeBack = fWallSize*0.95;
			float fScalingFactor = fWallSize / (float)nTextureHeight;
			float fScalingFactorBack = fWallSizeBack / (float)nTextureHeight;
			entities[2*x].setX(x);
			entities[2*x].setY(nScreenHeight/2.0f - fWallSize/2.0f);
			entities[2*x+1].setX(x);
			entities[2*x+1].setY(nScreenHeight/2.0f - fWallSizeBack/2.0f);
			float fColorFactor = 4.0f*fWallSize/(float)nScreenWidth;
			if(fColorFactor>1){
				fColorFactor = 1;
			}
			entities[2*x].darken(fColorFactor);
			entities[2*x].setSize(fScalingFactor);
			entities[2*x+1].setSize(fScalingFactorBack);
			entities[2*x].setIdentifier(dDepthBuffer[x].nTextureIdentifier-1);
			entities[2*x+1].setIdentifier(dDepthBuffer[x].nTextureIdentifier+3);
			entities[2*x].setSample(dDepthBuffer[x].sample);
			entities[2*x+1].setSample(dDepthBuffer[x].sample);
			
			window.render(entities[2*x+1]);
			window.render(entities[2*x]);
		}
		if (bCanMoveY)
				fPlayerY += fNewY;
			if(bCanMoveX)
				fPlayerX += fNewX;
		int nHandSize = 10;
		int nHandW = 15;
		int nHandH = 18;
		window.render(hands, nHandSize, (nScreenWidth-nHandW*nHandSize)/2.0f, nScreenHeight-nHandH*nHandSize, 15, 18);
		window.display();
	}
	window.cleanUp();
	SDL_Quit();
	return 0;
}