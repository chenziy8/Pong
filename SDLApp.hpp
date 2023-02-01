#pragma once
#ifndef  SDLAPP_HPP
#define SDLAPP_HPP
// Note: If you want SDL to build on multiple platforms, for now
//       this is the easiest solutoin to get SDL building on multiple
//       paths for this class.
//       A better solution is to use sdl-config --cflags --libs in the
//       build system.
#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#else
	// Windows and Mac use a different path
	// If you have compilation errors, change this as needed.
#include <SDL.h>

#endif
#include <functional>



class SDLApp {
public:
	SDLApp(Uint32 subsystemFlags, const char* title, int x, int y, int w, int h);
	~SDLApp();
	void RunLoop();
	void StopAppLoop();
	SDL_Renderer* GetRenderer() const;
	int GetHeight();
	int GetWidth();
	void SetRenderCallback(std::function<void(void)> func);
	void SetEventCallback(std::function<void(void)> func);
	void SetUpdateCallback(std::function<void(void)> func);
	SDL_Texture* GetFontTexture();
private:
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
	SDL_Rect m_fontHolder;
	SDL_Surface* m_leftScoreSurface;
	SDL_Texture* m_leftScoreTexture;
	
	bool m_gameIsRunning = true;
	int m_width;
	int m_height;
	std::function<void(void)> m_RenderCallback;
	std::function<void(void)> m_EventCallback;
	std::function<void(void)> m_UpdateCallback;
};
#endif // ! SDLAPP_HPP
