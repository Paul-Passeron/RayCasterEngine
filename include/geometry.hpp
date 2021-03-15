

#pragma once
struct point{
	float x, y;
};
struct line{
	point p1, p2;
	int nTextureIdentifier;
};
struct depthElement{
	float dist, sample;
	int nTextureIdentifier;
};

point line_line_intersection(line& l1, line& wall);
float dist(point& p1, point& p2);
int getId(int p_textureNumber, int p_columnIndex);

