#include "Texture.hpp"
#include "ResourceManager.hpp"
Texture::Texture(SDL_Renderer* renderer, std::string path) {
	SDL_Surface* surface = ResourceManager::Instance().GetSurface(path);
	m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	m_rectangle.x = 0;
	m_rectangle.y = 0;
	m_rectangle.w = 10;
	m_rectangle.h = 32;
}

Texture::~Texture() {
	SDL_DestroyTexture(m_texture);
}

void Texture::SetPosition(int x, int y) {

	m_rectangle.x = x;
	m_rectangle.y = y;
}

void Texture::SetSize(int w, int h) {
	m_rectangle.w = w;
	m_rectangle.h = h;
}


void Texture::Render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, m_texture, NULL, &m_rectangle);
}


int Texture::GetPositionX() {
	return m_rectangle.x;
}

int Texture::GetPositionY() {
	return m_rectangle.y;
}

int Texture::GetSizeHeight() {
	return m_rectangle.h;
}

int Texture::GetSizeWidth() {
	return m_rectangle.w;
}