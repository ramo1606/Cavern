#pragma once
#include "CollideActor.h"
#include "Bolt.h"

using namespace Common;

constexpr int MAX_TIMER = 250;

/*
* Orb is a CollideActor, this is the Orb/Bubble that the character will spawn every time we press space.
*/
class Orb : public CollideActor
{
public:
	Orb(Vector2 pos, float dirX);
	Orb(const Orb&) = default;
	Orb& operator=(const Orb&) = default;
	virtual ~Orb() = default;

	void update() override;
	bool hitTest(Bolt& bolt);

	void setTrappedEnemyType(ROBOT_TYPE type) { m_TrappedEnemyType = type; }
	void setBlownFrames(int value) { m_BlownFrames = value; }
	void setFloating(bool isFloating) { m_Floating = isFloating; }
	
	int getTimer() const{ return m_Timer; };
	int getBlownFrames() const { return m_BlownFrames; }
	ROBOT_TYPE getTrappedEnemyType() const { return m_TrappedEnemyType; }

private:
	bool m_Floating{ false };
	ROBOT_TYPE m_TrappedEnemyType{ ROBOT_TYPE::NONE }; //Which type of enemy is trapped in this bubble
	int m_Timer{ -1 };
	int m_BlownFrames{ 6 };		//Number of frames during which we will be pushed horizontally
};