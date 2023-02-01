#include "SDLApp.hpp"
#include "GameObject.hpp"
#include <iostream>
#include <functional>
SDLApp::SDLApp(Uint32 subsystemFlags, const char* title, int x, int y, int w, int h) {
	m_width = w;
	m_height = h;
	if (SDL_Init(subsystemFlags) < 0) {
		std::cout << "SDL could not be initialized: " << SDL_GetError();
	}
	else {
		std::cout << "SDL video system is ready\n";
	}
	m_window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN);
	m_renderer = SDL_CreateRenderer(m_window, 01, SDL_RENDERER_ACCELERATED);
	
}

SDLApp::~SDLApp() {
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}


void SDLApp::RunLoop() {
	
	while (m_gameIsRunning) {
		Uint32 start = SDL_GetTicks();
		m_EventCallback();
		m_UpdateCallback();
		SDL_RenderClear(m_renderer);
		m_RenderCallback();
		SDL_RenderPresent(m_renderer);
		Uint32 elapsedTime = SDL_GetTicks() - start;
		if (elapsedTime < 16) {
			SDL_Delay(16 - elapsedTime);
		}
	}
}

void SDLApp::StopAppLoop() {
	m_gameIsRunning = false;
}

SDL_Renderer* SDLApp::GetRenderer() const {
	return m_renderer;
}
int SDLApp::GetHeight() {
	return m_height;
}

int SDLApp::GetWidth() {
	return m_width;
}

void SDLApp::SetRenderCallback(std::function<void(void)> func) {
	m_RenderCallback = func;
}

void SDLApp::SetEventCallback(std::function<void(void)> func) {
	m_EventCallback = func;
}

void SDLApp::SetUpdateCallback(std::function<void(void)> func) {
	m_UpdateCallback = func;
}
