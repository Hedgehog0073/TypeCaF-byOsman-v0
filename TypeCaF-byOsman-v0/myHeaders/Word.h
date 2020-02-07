#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <fstream>
#include <time.h>
#include <random>
#include <string>
#define font 25

struct Word
{
	int init(const char* text);
	int move(int x , int y);
	int addLetter(char* text);
	int clearLetter();
	void clear();
	void getline();
	std::string word;
	std::string tp;
	int score = 0;
	void render(std::string wordRender, int x ,int y,int w, int h);

private:

	SDL_Surface* loadingSrf;
	SDL_Texture* texture;

	SDL_Rect scoreRect;

	void render();
	TTF_Font* bold = TTF_OpenFont("ttf/bold.ttf", 50);
	SDL_Color red = { 200,0,0 };
	SDL_Rect textBox;
	SDL_Rect wordRect;

	void render(std::string wordRender, SDL_Rect textbox);

};