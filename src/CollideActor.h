#pragma once
#include "Actor.h"

/*
* This class is a child of Actor class, it is basically an actor that will check for 
* collisions with blocks in the game every time the actor moves.
*/
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