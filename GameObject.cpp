#include "GameObject.hpp"
#include "Text.hpp"
#include <iostream>
GameObject::GameObject() {
	m_sprite = NULL;
}

GameObject::GameObject(SDL_Renderer* renderer) {
	m_sprite = NULL;
	m_renderer = renderer;
}

GameObject::~GameObject() {
	if (m_sprite != NULL) {
		delete m_sprite;
	}
}

void GameObject::Update() {}

void GameObject::Render() {
	if (m_sprite != NULL) {
		//std::cout << "Hello from GameObject: Render with sprite!" << std::endl;
		m_sprite->Render(m_renderer);
	}
	else {
		std::cout << "Hello from GameObject: No sprite found!" << std::endl;
	}
}

void GameObject::AddTexture(std::string path) {
	m_sprite = new Texture(m_renderer, path);
}

void GameObject::SetPosition(int x, int y) {
	if (m_sprite != NULL) {
		m_sprite->SetPosition(x, y);
	}
}

void GameObject::SetSize(int w, int h) {
	if (m_sprite != NULL) {
		m_sprite->SetSize(w, h);
	}
}

Texture* GameObject::GetTexture() {
	return m_sprite;
}

void GameObject::AddCollider2D() {
	m_collider = new Collider2D();
	m_collider->SetSize(m_sprite);
	m_collider->SetPosition(m_sprite);
}

Collider2D* GameObject::GetCollider2D() {
	return m_collider;
}