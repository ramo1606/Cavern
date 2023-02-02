#pragma once
#include "Actor.h"

using namespace Common;

/*
* Pop Animation actor
*/
class Pop : public Actor
{
public:
	Pop(Vector2 pos, POP_TYPE type = POP_TYPE::FRUIT);
	Pop(const Pop&) = default;
	Pop& operator=(const Pop&) = default;
	virtual ~Pop() = default;

	void update() override;
	bool isAlive() const { return m_Timer < 12; }

private:
	POP_TYPE m_Type{ POP_TYPE::FRUIT };
	int m_Timer{ -1 };
};