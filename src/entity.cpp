#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.hpp"
#include "geometry.hpp"
#include <iostream>
Entity::Entity(float p_x, float p_y, SDL_Texture* p_tex, float p_size, int p_id=1, float p_sample=0.0f)
:x(p_x), y(p_y), tex(p_tex), size(p_size), id(p_id)
{
	currentFrame.x = (p_sample);
	currentFrame.y = 0;
	currentFrame.w = 1;
	currentFrame.h = 32;
}
float Entity::getX(){
	return x;
}
float Entity::getY(){
	return y;
}

SDL_Texture* Entity::getTex(){
	return tex;
}

SDL_Rect Entity::getCurrentFrame(){
	return currentFrame;
}

float Entity::getSize(){
	return size;
}

void Entity::setSize(float p_size){
	size = p_size;
}

void Entity::setX(float p_x){
	x = p_x;
}

void Entity::setY(float p_y){
	y = p_y;
}
/*void Entity::set(float p_x, float p_y, SDL_Texture* p_tex, float p_size, int p_id, float p_sample){
	x = p_x;
	y = p_y;
	id = p_id;
	tex = p_tex;
	size = p_size;
	sample = p_sample;
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 1;
	currentFrame.h = 32;
}*/
void Entity::setIdentifier(int p_id){
	id = p_id;
}

int Entity::getId(){
	return id;
}

float Entity::getSample(){
	return currentFrame.x;
}
void Entity::darken(float a){
	SDL_SetTextureColorMod(tex, 255.0f*a, 255.0f*a, 255.0f*a);
}

void Entity::setSample(float p_sample){
	currentFrame.x = p_sample*32.0f;
}