#include "screen.h"
#include "shapes.h"
#include "vec3.h"
#include <iostream>
#include <vector>
#include <stdlib.h>

int main(void){

	float rotation = 0.04;

	int prevXPosition;
	int prevYPosition;

	int x = 50;
	int y = 50;

	int a = 100;

	int selection = 0;

	std::vector<Shape> loadedShapes;

	Shape * currentSelection = NULL;

	Screen screen;

	loadedShapes.push_back(Cube(250,200,1000,100,100,100));
	loadedShapes.push_back(Pyramid(250,200,100,100));
	loadedShapes.push_back(Cube(250,200,1000,100,100,50));

	currentSelection = &(loadedShapes[selection]);

	currentSelection->setCentroid();

	bool running = true;

	int selected = 0;

	float deltaX = 0.0;
	float deltaY = 0.0;

	while(running){

		while(SDL_PollEvent(&(screen.e))){

			if(screen.e.type == SDL_KEYDOWN && screen.e.key.keysym.sym == SDLK_SPACE){

				selection = (selection + 1) % loadedShapes.size();

				currentSelection = &(loadedShapes[selection]);

				currentSelection->setCentroid();

			}

			if(screen.e.type == SDL_MOUSEBUTTONDOWN && screen.e.button.button == SDL_BUTTON_LEFT){

				selected = 1;

				prevXPosition = screen.e.button.x / 2;
				prevYPosition = screen.e.button.y / 2;

			}

			if(screen.e.type == SDL_MOUSEBUTTONUP && screen.e.button.button == SDL_BUTTON_LEFT){

				selected = 0;

			}

			if(screen.e.type == SDL_MOUSEWHEEL){

				currentSelection->resize(screen.e.wheel.y < 0 ? 0.95 : 1.05);

			}

			if(screen.e.type == SDL_MOUSEMOTION && selected){

				int threshold = 1;

				int deltaX = (screen.e.motion.x / 2) - prevXPosition;
				int deltaY = (screen.e.motion.y / 2) - prevYPosition;

				if(deltaX <= -threshold) deltaX = -1;
				else if(deltaX >= threshold) deltaX = 1;
				else deltaX = 0;

				if(deltaY <= -threshold) deltaY = -1;
				else if(deltaY >= threshold) deltaY = 1;
				else deltaY = 0;

				prevXPosition = (screen.e.motion.x / 2);
				prevYPosition = (screen.e.motion.y / 2);

				if(deltaX || deltaY) currentSelection->rotateShape(screen, deltaY * rotation, deltaX * rotation, 0.0);


			}

			if(screen.e.type == SDL_QUIT) running = 0;

	}

		currentSelection->draw(screen);


		screen.show();
		screen.clear();

		screen.input();
		SDL_Delay(30);

	}

	SDL_DestroyWindow(screen.window);
	SDL_Quit();

	return 0;

}
