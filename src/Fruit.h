#pragma once
#include "GravityActor.h"

using namespace Common;

class Fruit : public GravityActor
{
public:
	Fruit(Vector2 pos, ROBOT_TYPE trapped_enemy_type = ROBOT_TYPE::NORMAL);
	Fruit(const Fruit&) = default;
	Fruit& operator=(const Fruit&) = default;
	virtual ~Fruit() = default;

	void update() override;

	bool isDead() const { return m_TimeToLive <= 0; };

private:
	FRUIT_TYPE m_Type{ FRUIT_TYPE::APPLE };
	int m_TimeToLive{ 500 };
};