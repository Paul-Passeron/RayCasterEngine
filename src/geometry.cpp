#include "geometry.hpp"
#include <math.h>

point line_line_intersection(line& l1, line& wall){

	point p = { 1000.0f, 1000.0f };
	float x1 = wall.p1.x;
	float y1 = wall.p1.y;
	float x2 = wall.p2.x;
	float y2 = wall.p2.y;
	float x3 = l1.p1.x;
	float y3 = l1.p1.y;
	float x4 = l1.p2.x;
	float y4 = l1.p2.y;
	float D = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (D != 0) {
		float  t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / D;
		float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) /D;

		if (t > 0 && t < 1 && u > 0) {
			p.x = x1 + t * (x2 - x1);
			p.y = y1 + t * (y2 - y1);
		}
	}
	return p;
}


point llinter(line& l1, line& wall){

	point p = { 1000.0f, 1000.0f };
	float x1 = wall.p1.x;
	float y1 = wall.p1.y;
	float x2 = wall.p2.x;
	float y2 = wall.p2.y;
	float x3 = l1.p1.x;
	float y3 = l1.p1.y;
	float x4 = l1.p2.x;
	float y4 = l1.p2.y;
	float D = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (D != 0) {
		float  t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / D;
		float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) /D;
if (t > 0 && t < 1) {
		p.x = x1 + t * (x2 - x1);
		p.y = y1 + t * (y2 - y1);
		
	}}
	return p;
}


float dist(point& p1, point& p2){
	return sqrtf((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}


int getId(int p_textureNumber, int p_columnIndex){
	return (p_columnIndex + p_textureNumber)*32;
}
