#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Word.h"
#include <string>

extern SDL_Renderer* wRenderer;
extern int windowX;
extern int windowY;
extern bool gg;
int Word::init(const char* text)
{
	//word = (wchar_t*)text;
	word = text;
	textBox.w = word.length() * font;
	textBox.h = font * 2;
	textBox.y = windowY - textBox.h;
	textBox.x = (windowX / 2) - (textBox.w / 2);

	wordRect.w = 100;
	wordRect.h = font * 2;
	wordRect.y = 0;
	wordRect.x = windowX / 2 - wordRect.w / 2;

	scoreRect.h = font * 8;
	scoreRect.y = 0;
	scoreRect.w = font * 4;
	scoreRect.x = windowX - scoreRect.w;

	getline();

	//render();

	return 0;
}
void Word::render(std::string wordRender, int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	
	
	loadingSrf = TTF_RenderText_Solid(bold,wordRender.c_str(), red);
	texture = SDL_CreateTextureFromSurface(wRenderer, loadingSrf);
	SDL_RenderCopy(wRenderer, texture, 0, &rect);
	SDL_FreeSurface(loadingSrf);
	SDL_DestroyTexture(texture);

}
void Word::render(std::string wordRender, SDL_Rect textbox)
{


	loadingSrf = TTF_RenderText_Solid(bold, wordRender.c_str(), red);

	texture = SDL_CreateTextureFromSurface(wRenderer, loadingSrf);
	SDL_RenderCopy(wRenderer, texture, 0, &textbox);
	SDL_FreeSurface(loadingSrf);
	SDL_DestroyTexture(texture);
	SDL_SetRenderDrawColor(wRenderer, 255, 0, 0, 255);

	SDL_RenderDrawLine(wRenderer, 0, windowY - font * 2, windowX, windowY - font * 2);
	SDL_SetRenderDrawColor(wRenderer, 20, 200, 150, 255);


}

void Word::render()
{
	render(word, textBox);
	render(tp, wordRect);
	render(std::to_string(score), scoreRect);
}

int Word::move(int x, int y)
{
	wordRect.y += y;

	if (wordRect.y + wordRect.h == windowY - font * 2)
	{
		gg = true;
		word = "";
		SDL_RenderClear(wRenderer);
		render("GAME OVER IF YOU WANT TO SAVE YOUR SCORE PLS ENTER YOUR NAME", 0, windowY / 2, windowX, 50);
		SDL_RenderPresent(wRenderer);
		return 0;
		
	}
	render();

	return 1;
}
int Word::addLetter(char* text)
{

	//word += (wchar_t*)text;
	word += text;
	textBox.x += -font / 2;
	textBox.w = word.length() * font;
	if (gg)
	{
		render(word, textBox);
		render("GAME OVER IF YOU WANT TO SAVE YOUR SCORE PLS ENTER YOUR NAME", 0, windowY / 2, windowX, 50);

		return 0;
	}
	render();
	return 0;
}

int Word::clearLetter()
{

	//word += (wchar_t*)text;
	if (word == "")
	{
		return -1;
	}
	word.pop_back();
	textBox.x += font / 2;
	textBox.w = word.length() * font;
	render();

	return 0;
}
void Word::clear()
{



	if (word == tp)
	{
		score += 1;

	}
	else if (score == 0);
	else
	{
		score -= 1;
	}


	wordRect.y = 0;

	/*word.clear();
	textBox.w = word.length() * font;
	textBox.x = (windowX / 2) - (textBox.w / 2);
	*/
	getline();
	render();

}
void Word::getline()
{
	std::fstream newfile;
	newfile.open("words/words_alpha.txt", std::ios::in); //open a file to perform read operation using file object
	if (newfile.is_open()) {   //checking whether the file is open


		int debug = rand();
		std::default_random_engine generator(debug);
		std::uniform_int_distribution<int> distribution(1, 4234899);
		int b = distribution(generator);
		newfile.seekg(b);
		//newfile.seekg(0, std::ios_base::end); NOTE(OSMAN): BU OPTIMIZASYONDAN SONRA OYUN KOŞMAYA BAŞLADI YAWWWW
		//int a = newfile.tellg();
			char i = '\0';
		while (i != '\n')
		{
			newfile.seekg(1,std::ios_base::cur);
			newfile.read(&i, 1);

		}
		
		std::getline(newfile, tp);

		/*for (int i = 0; i < b; i++)
		{
			std::getline(newfile, tp);
		}*/
		word.clear();
		textBox.w = word.length() * font;
		textBox.x = (windowX / 2) - (textBox.w / 2);

		wordRect.w = tp.length() * font;
		wordRect.x = windowX / 2 - wordRect.w / 2;
		
		render();

	}
}
