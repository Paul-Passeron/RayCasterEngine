#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity
{
public:
	Entity(float p_x, float p_y, SDL_Texture* p_tex, float p_size, int p_id, float p_sample);
	float getX();
	float getY();
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	float getSize();
	void setSize(float p_size);
	void setX(float p_x);
	void setY(float p_y);
	//void set(float p_x, float p_y, SDL_Texture* p_tex, float p_size, int p_id);
	void setIdentifier(int p_id);
	int getId();
	float getSample();
	void setSample(float p_sample);
private:
	float x, y, size;
	int id;
	SDL_Texture* tex;
	SDL_Rect currentFrame;
	
};

