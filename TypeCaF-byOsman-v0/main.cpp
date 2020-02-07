#include <iostream>
#include <SDL.h>
#include "myHeaders/Game.h"
#define SHAPE_SIZE 30
int difficulty = 10;
int windowX = 1280;
int windowY = 720;
bool gg = false;



SDL_Window* mWindow = SDL_CreateWindow("TYPE CORRECT AND FAST BY OSMAN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowX, windowY, 0);
SDL_Renderer* wRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
SDL_Texture* texture = nullptr;
void logScore(std::string name, GAME hello);


int main(int argc, char* argv[])
{

	//_setmode(_fileno(stdout), _O_U16TEXT);              NOTE(OSMAN): MAKING GAME IN TURKISH IS DEPRECATED !!!


	bool openWindow = true;
	TTF_Init();
	srand(time(NULL));
	SDL_Event event;
	SDL_SetRenderDrawColor(wRenderer, 20, 200, 150, 255);
	SDL_RenderClear(wRenderer);

	GAME hello;
	hello.Start();

	SDL_RenderPresent(wRenderer);




	SDL_StartTextInput();
	SDL_RenderPresent(wRenderer);

	while (openWindow)
	{


		if (!gg)
			SDL_RenderClear(wRenderer);
		if (SDL_PollEvent(&event))
		{


			switch (event.type)
			{

			case SDL_QUIT:
				openWindow = false;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					openWindow = false;
					break;
				case SDLK_RIGHT:
					SDL_RenderClear(wRenderer);
					hello.x.move(10, 0);
					SDL_RenderPresent(wRenderer);
					break;
				case SDLK_LEFT:
					SDL_RenderClear(wRenderer);
					hello.x.move(-10, 0);
					SDL_RenderPresent(wRenderer);
					break;
				case SDLK_RETURN:
					SDL_RenderClear(wRenderer);
					if (gg)
					{
						logScore(hello.x.word, hello);
						openWindow = false;
						break;
					}
					hello.x.clear();
					SDL_RenderPresent(wRenderer);

					break;
				case SDLK_BACKSPACE:
					SDL_RenderClear(wRenderer);
					hello.x.clearLetter();
					//	hello.x.clear();
					SDL_RenderPresent(wRenderer);

					break;


				}

			case SDL_TEXTINPUT:
				if (*event.text.text != '\x1')
				{
					if (hello.x.word.length() == 50)
					{
						break;
					}
					SDL_RenderClear(wRenderer);
					hello.x.addLetter(event.text.text);

					SDL_RenderPresent(wRenderer);
					break;

				}

				break;
			}
		}
		if (!gg)
		{

			hello.x.move(0, 1);
			SDL_RenderPresent(wRenderer);
			static int delay = difficulty - hello.x.score / 5;
			if (delay <= 0)
				delay = 0;
			SDL_Delay(delay); //NOTE(OSMAN): HARD CODE !!!
		}
		else
			SDL_Delay(difficulty);
	}

	return 0;
}
void logScore(std::string name, GAME hello)
{

	std::fstream list;
	list.open("SCORES.txt", std::fstream::out| std::fstream::app);
	hello.x.score = 11;
	
	list << name << "'s score is " << hello.x.score << std::endl;
	std::string queue[11];
	int topNumb = 0;
	std::string buffer;
	int index = 0;
	list.close();
	list.open("SCORES.txt", std::fstream::in);
		for (int i = 0; i < 11; i++)
		{
			std::getline(list, queue[i]);
		}
		list.close();


		list.open("SCORES.txt", std::fstream::out | std::fstream::trunc);
		list.close();

		list.open("SCORES.txt", std::fstream::out | std::fstream::app);


		for (int i = 10; i >= 1; i--)
		{
			for (int a = 0; a < i+1; a++)
			{
				std::string sacma;
				
				sacma = queue[a].substr(queue[a].find("'s score is ",0) + 12, queue[a].length() - queue[a].find("'s score is ", 0)-12);
				if (topNumb < std::stoi(sacma))
				{
					
					topNumb = std::stoi(sacma);
					index = a;
				}
			}
				list << queue[index] << std::endl;
				buffer = queue[i];
				queue[i] = queue[index];
				queue[index] = buffer;
				topNumb = 0;
				index = 0;
				buffer = "";
		}
	


		list.close();





	

	
}
