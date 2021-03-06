#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "geometry.hpp"
#include <iostream>
#include <entity.hpp>
class RenderWindow{

public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath); 
	void cleanUp();
	void clear();
	void render(Entity& p_entity);
	void render(SDL_Texture* p_tex, float p_size, float x, float y, float w, float h);
	void display();
	void setIcon(SDL_Surface* icon);
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};

