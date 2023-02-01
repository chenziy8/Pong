#include "Text.hpp"


void Text::Init(SDL_Renderer* renderer) {
	if (TTF_Init() == -1) {
		std::cout << "Could not init TTF" << std::endl;
	}
	m_font = TTF_OpenFont("media/arial.ttf",30);
	if (m_font == nullptr) {
		std::cout << "Hello from Text.cpp: no font" << std::endl;
		//exit(-1);
	}
	m_rec.x = 50;
	m_rec.y = 50;
	m_rec.w = 100;
	m_rec.h = 100;
	m_renderer = renderer;
	
}

void Text::Render(std::string score = "0") {
	m_surface = TTF_RenderText_Solid(m_font, score.c_str(), {255,255,255});
	m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
	SDL_FreeSurface(m_surface);
	SDL_RenderCopy(m_renderer, m_texture, NULL, &m_rec);
}

void Text::SetPosition(int x, int y) {
	m_rec.x = x;
	m_rec.y = y;
}

void Text::SetDimension(int w, int h) {
	m_rec.w = w;
	m_rec.h = h;
}

void Text::Update(int score) {

}

