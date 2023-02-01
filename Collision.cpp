#include "Collision.hpp"

Collider2D::Collider2D() {
	m_colliderRectangle = new SDL_Rect;
	m_colliderRectangle->x = 0;
	m_colliderRectangle->y = 0;
	m_colliderRectangle->w = 0;
	m_colliderRectangle->h = 0;
}

Collider2D::~Collider2D() {

}

SDL_Rect* Collider2D::GetCollider() {
	return m_colliderRectangle;
}

SDL_bool Collider2D::IsColliding( Collider2D& collider) {
	if (m_colliderRectangle == nullptr) {
		return SDL_FALSE;
	}
	SDL_Rect* temp = collider.m_colliderRectangle;
	if (temp == nullptr) {
		return SDL_FALSE;
	}
	return SDL_HasIntersection(m_colliderRectangle, temp);
}

void  Collider2D::SetSize(Texture* object) {
	m_colliderRectangle->w = object->GetSizeWidth();
	m_colliderRectangle->h = object->GetSizeHeight();

}
void  Collider2D::SetPosition(Texture* object) {
	m_colliderRectangle->x = object->GetPositionX();
	m_colliderRectangle->y = object->GetPositionY();
}
int Collider2D::getY() {

	return	m_colliderRectangle->y;
}

