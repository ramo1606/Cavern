#pragma once
#include "CollideActor.h"

constexpr float MAX_FALL_SPEED = 10.f;

/*
* GravityActor is a CollideActor but is also affected by gravity
*/
class GravityActor : public CollideActor
{
public:
	GravityActor(Vector2 pos, Texture2D* image = nullptr);
	GravityActor(const GravityActor&) = default;
	GravityActor& operator=(const GravityActor&) = default;
	virtual ~GravityActor() = default;

	void update(bool detect = true);

protected:
	bool m_Landed{ false };
	float m_VelY{ 0.f };
};