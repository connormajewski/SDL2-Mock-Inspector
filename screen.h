#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <vector>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

const int scaleX = 2;
const int scaleY = 2;

class Screen{

	public:

	SDL_Event e;
	SDL_Window * window;
	SDL_Renderer * renderer;
	std::vector<SDL_FPoint> points;

	Screen(){

		SDL_Init(SDL_INIT_VIDEO);
		SDL_CreateWindowAndRenderer(
			640*scaleX, 480*scaleY, 0, &window,&renderer);
		SDL_RenderSetScale(renderer,scaleX,scaleY);

		SDL_WarpMouseInWindow(window, (640*scaleX) / 2, (640*scaleY) / 2);

	}

	void pixel(float x, float y){

		SDL_FPoint temp = SDL_FPoint();

		temp.x = x;
		temp.y = y;

		points.emplace_back(temp);

	}

	void show(){

		SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
		SDL_RenderClear(renderer);

		int color = 0xFF;

		for(auto& point : points){

			SDL_SetRenderDrawColor(renderer, color, color, color, color);

			SDL_RenderDrawPointF(renderer, point.x, point.y);

			color--;

			if(!color) color = 0xFF;

		}


		SDL_RenderPresent(renderer);

	}

	void clear(){

		points.clear();

	}

	void input(){

		while(SDL_PollEvent(&e)){

			if(e.type == SDL_QUIT){

				SDL_Quit();
				exit(0);

			}

		}

	}

};

#endif
