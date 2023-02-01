#pragma once
#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <string>
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
class Texture {
public:	
	Texture(SDL_Renderer* renderer, std::string path);
	~Texture();
	void SetPosition(int x, int y);
	void SetSize(int w, int h);
	int GetPositionX();
	int GetPositionY();
	int GetSizeHeight();
	int GetSizeWidth();
	void Update();
	void Render(SDL_Renderer* renderer);
private:
	inline SDL_Rect GetRectangle() const {
		return m_rectangle;
	}
	SDL_Rect m_rectangle;
	SDL_Texture* m_texture;

};

#endif
