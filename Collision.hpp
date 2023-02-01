#pragma once
#ifndef COLLISION_HPP
#define COLLISION_HPP
// Note: If you want SDL to build on multiple platforms, for now
//       this is the easiest solutoin to get SDL building on multiple
//       paths for this class.
//       A better solution is to use sdl-config --cflags --libs in the
//       build system.
#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>

#else
	// Windows and Mac use a different path
	// If you have compilation errors, change this as needed.
#include <SDL.h>
#endif
#include <string>
#include "Texture.hpp"

class Collider2D {
public:
	Collider2D();
	~Collider2D();
	SDL_bool IsColliding(Collider2D& collider);
	SDL_Rect* GetCollider();
	void SetSize(Texture* object);
	void SetPosition(Texture* object);
	int getY();
	

private:
	SDL_Rect* m_colliderRectangle;

};
#endif
