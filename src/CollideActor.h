#pragma once
#include "Actor.h"

class CollideActor : public Actor 
{
public:
	CollideActor(Vector2 pos, Texture2D* image = nullptr);
	CollideActor(const CollideActor&) = default;
	CollideActor& operator=(const CollideActor&) = default;
	virtual ~CollideActor() = default;

	virtual void update() override;
	bool move(int dx, int dy, int speed);

	float getDirectionX() const { return m_DirectionX; }
	void setDirectionX(float val) { m_DirectionX = val; }

protected:
	float m_DirectionX{ 0.f };
};