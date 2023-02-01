#include "ResourceManager.hpp"
#include <iostream>
ResourceManager::ResourceManager() {
	
}

ResourceManager& ResourceManager::Instance() {
	/*if (ResourceManager::instance_ == NULL) ResourceManager::instance_ = new ResourceManager();
	return *instance_;*/
	static ResourceManager* s_instance = new ResourceManager;
	return *s_instance;
}

SDL_Surface* ResourceManager:: GetSurface(std::string path) {
	auto hasSurface = m_surface.find(path);
	if (hasSurface != m_surface.end()) {
		std::cout << "Hello from ResourceManager:found your texture!" << std::endl;
		return m_surface[path];
	}
	else {
		std::cout << "Hello from ResourceManager:Add new texture!" << std::endl;
		SDL_Surface* surface = SDL_LoadBMP(path.c_str());
		m_surface.insert(std::make_pair(path, surface));
		return m_surface[path];
	}
}