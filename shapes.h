#ifndef SHAPES_H
#define SHAPES_H

#include "screen.h"
#include "vec3.h"
#include <vector>
#include <iostream>

class Shape{

	public:

	std::vector<vec3> vertices;
	std::vector<edge> edges;
	vec3 centroid{0,0,0};

	int xc;
	int yc;

	float width;
	float height;
	float depth;

	void setCentroid(){

		centroid.x = 0;
		centroid.y = 0;
		centroid.z = 0;

		for(auto& v : vertices){

			centroid.x += v.x;
			centroid.y += v.y;
			centroid.z += v.z;

		}

		centroid.x /= vertices.size();
		centroid.y /= vertices.size();
		centroid.z /= vertices.size();


	}

	void rotateShape(Screen& screen, float xRotation = 1.0, float yRotation = 1.0, float zRotation = 1.0){

		for(auto& v : vertices){

			v.x -= centroid.x;
			v.y -= centroid.y;
			v.z -= centroid.z;

			rotate(v, xRotation, yRotation, zRotation);

			v.x += centroid.x;
			v.y += centroid.y;
			v.z += centroid.z;

			screen.pixel(v.x, v.y);

		}


	}

	void resize(float size){

		for(auto& v : vertices){

			v.x *= size;
			v.y *= size;
			v.z *= size;

		}

		setCentroid();

		moveTo(xc + (width / 2),yc + (height / 2));

	}

	void draw(Screen& screen){

		for(auto& e : edges){

			line(screen, vertices[e.a].x, vertices[e.a].y,  vertices[e.b].x, vertices[e.b].y);

		}


	}

	void moveTo(float x, float y){

		moveShape(-(centroid.x - x), -(centroid.y - y), 0);

	}

	void moveShape(float x = 0, float y = 0, float z = 0){

		for(auto& v : vertices){

			v.x += x;
			v.y += y;

			if(z){

				v.x = centroid.x + z * (v.x - centroid.x);
				v.y = centroid.y + z * (v.y - centroid.y);
				v.z = centroid.z + z * (v.z - centroid.z);

			}


		}

		setCentroid();


	}

	int intersection(float mouseX, float mouseY){

		int inside = 0;
		int intersect;
		unsigned long i,j;

		for(i=0, j = vertices.size() - 1; i < vertices.size() - 1; j = i++){

			float xi = vertices[i].x;
			float yi = vertices[i].y;
			float xj = vertices[j].x;
			float yj = vertices[j].y;

			intersect = ((yi > mouseY) != (yj > mouseY)) && (mouseX < (xj - xi) * (mouseY - yi) / (yj - yi) + xi);

			if(intersect) inside = !inside;

		}

		return inside;

	}
};

class Cube : public Shape {

	public:

	Cube(float x, float y, float z, float w, float h, float d){

		vertices = {

			{x,y,z},
			{x+w,y,z},
			{x,y,z+d},
			{x+w,y,z+d},

			{x,y+h,z},
			{x+w,y+h,z},
			{x,y+h,z+d},
			{x+w,y+h,z+d}

		};

		edges = {

		{0,4},
		{1,5},
		{2,6},
		{3,7},

		{0,1},
		{1,3},
		{2,0},
		{3,2},

		{4,5},
		{5,7},
		{6,4},
		{7,6},

		};

		xc = x;
		yc = y;

		width = w;
		height = h;

	}
};

class Pyramid: public Shape{

	public:

	Pyramid(float x, float y, float w, float h){

		edges = {

			{0,1},
			{1,3},
			{3,2},
			{2,0},

			{0,4},
			{1,4},
			{2,4},
			{3,4},

		};

		vertices = {

			{x, y, 0},
			{x+w, y, 0},
			{x, y+h, 0},
			{x+w, y+h, 0},
			{x+(w/2), y + (w/2), h}

		};

		xc = x;
		yc = y;

		width = w;
		height = h;

	}
};

#endif
