#pragma once
#include "Actor.h"

class CollideActor : public Actor 
{
public:
	CollideActor(Vector2 pos, Texture2D* image = nullptr);
	CollideActor(const CollideActor&) = default;
	CollideActor& operator=(const CollideActor&) = default;
	virtual ~CollideActor() = default;

	bool move(int dx, int dy, int speed);

	void setDirectionX(float val) { m_DirectionX = val; }
	float getDirectionX() { return m_DirectionX; }

protected:
	float m_DirectionX{ 0.f };
};