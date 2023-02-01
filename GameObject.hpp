#pragma once
#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP
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
#include <vector>
#include "Collision.hpp"
#include "Texture.hpp"
class GameObject {
public:
	GameObject();
	GameObject(SDL_Renderer* renderer);
	~GameObject();
	void AddTexture(std::string sprite);
	void Update();
	void Render();
	void SetPosition(int x, int y);
	void SetSize(int w, int h);
	Texture* GetTexture();
	void AddCollider2D();
	Collider2D* GetCollider2D();
private:
	SDL_Renderer* m_renderer;
	Texture* m_sprite;
	Collider2D* m_collider;
};

#endif
