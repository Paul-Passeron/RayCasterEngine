
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<iostream>
#include"RenderWindow.hpp"
#include "entity.hpp"
#include "geometry.hpp"
RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = (SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED,  SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN));
	if(window==NULL){
		std::cout<<"Error: "<<SDL_GetError()<<std::endl;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath){
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);
	if(texture == NULL){
		std::cout<<"Failed to load texture: "<<SDL_GetError()<<std::endl;
	}
	return texture;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear(){
	SDL_RenderClear(renderer);
}



void RenderWindow::render(Entity& p_entity){
	SDL_Rect src;
	src.x = p_entity.getSample() + p_entity.getId()*32.0f;
	//std::cout<<src.x<<std::endl;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getX();
	dst.y = p_entity.getY();
	dst.w = p_entity.getCurrentFrame().w;
	dst.h = p_entity.getCurrentFrame().h*p_entity.getSize();


	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

void RenderWindow::display(){
	SDL_RenderPresent(renderer);
}