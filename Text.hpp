#pragma once
#ifndef TEXT_HPP
#define TEXT_HPP
#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#else
// Windows and Mac use a different path
// If you have compilation errors, change this as needed.
#include <SDL.h>
#endif
#include<iostream>
#include <string>
class Text {
public:
	void Init(SDL_Renderer* renderer);
	void Render(std::string score);
	void SetPosition(int x, int y);
	void SetDimension(int w, int h);
	void Update(int score);
private:
	TTF_Font* m_font;
	SDL_Surface* m_surface;
	SDL_Texture* m_texture;
	SDL_Rect m_rec;
	
	SDL_Renderer* m_renderer;
};
#endif