#include <iostream>
#include "Game.h"

extern SDL_Renderer* wRenderer;
extern int windowX;
extern int windowY;

int GAME::Start()
{
	//std::cout << "GAME IS STARTING..." << std::endl;

	
	x.init("");
	
	SDL_SetRenderDrawColor(wRenderer, 255, 0, 255, 255);
	SDL_RenderDrawLine(wRenderer, 0, windowY - font*2, windowX, windowY - font*2);
	SDL_SetRenderDrawColor(wRenderer, 0, 200, 0, 255);

	return 0;
}

