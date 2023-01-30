#pragma once
#include "GravityActor.h"

using namespace Common;

class Robot : public GravityActor
{
public:
	Robot(Vector2 pos, ROBOT_TYPE type = ROBOT_TYPE::NORMAL);
	Robot(const Robot&) = default;
	Robot& operator=(const Robot&) = default;
	virtual ~Robot() = default;

	void update() override;

	bool isAlive() const { return m_Alive; };

private:
	ROBOT_TYPE m_Type{ ROBOT_TYPE::NORMAL };
	int m_Speed{ 0 };
	int m_DirectionX{ 1 };
	bool m_Alive{ true };
	int m_ChangeDirTimer{ 0 };
	int m_FireTimer{ 100 };
};