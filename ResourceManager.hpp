#pragma once
#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP
#include <string>
#include <unordered_map>
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
class ResourceManager {
public:
	static ResourceManager& Instance();
	SDL_Surface* GetSurface(std::string path);

private:
	ResourceManager();
	//static ResourceManager* instance_ ;
	std::unordered_map<std::string, SDL_Surface*> m_surface;
};


#endif
