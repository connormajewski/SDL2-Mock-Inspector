#ifndef VEC3_H
#define VEC3_H

#include "screen.h"
#include <numeric>

struct vec3{

	float x;
	float y;
	float z;

};

struct edge{

	int a;
	int b;

};

void rotate(vec3& point, float x = 1, float y = 1, float z = 1){

        float rad = 0;

        vec3 originalPoint = point;

        rad = x;
        point.y = std::cos(rad) * originalPoint.y - std::sin(rad) * originalPoint.z;
        point.z = std::sin(rad) * originalPoint.y + std::cos(rad) * originalPoint.z;

        originalPoint = point;

        rad = y;
        point.x = std::cos(rad) * originalPoint.x - std::sin(rad) * originalPoint.z;
        point.z = std::sin(rad) * originalPoint.x + std::cos(rad) * originalPoint.z;

        originalPoint = point;

        rad = z;
        point.x = std::cos(rad) * originalPoint.x - std::sin(rad) * originalPoint.y;
        point.y = std::sin(rad) * originalPoint.x + std::cos(rad) * originalPoint.y;

}

void line(Screen& screen, float x1, float y1, float x2, float y2){

        float dx = x2 - x1;
        float dy = y2 - y1;

        float length = std::sqrt(dx * dx + dy * dy);

        float angle = std::atan2(dy, dx);

        for(float i =0;i<length;i++){

                screen.pixel(
                        x1 + std::cos(angle) * i,
                        y1 + std::sin(angle) * i
                        );

        }

}

#endif
