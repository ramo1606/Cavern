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

private:
};