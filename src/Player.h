#pragma once
#include "GravityActor.h"

class Player : public GravityActor 
{
public:
	Player(Vector2 pos, Texture2D* image = nullptr);
	Player(const Player&) = default;
	Player& operator=(const Player&) = default;
	virtual ~Player() = default;

	void update() override;
	void processInput() override;

	void reset();
	bool hitTest(CollideActor& other);

private:
	int m_Lives{ 2 };
	int m_Score{ 0 };
	int m_FireTimer{ 0 };
	int m_HurtTimer{ 100 };
	int m_Health{ 3 };
	int m_Dx{ 0 };
	//Orb* m_BlowingOrb{nullptr};
};