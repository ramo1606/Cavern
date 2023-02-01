#pragma once
#include "GravityActor.h"

class Orb;

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

	int getHealth() const { return m_Health; }
	int getLives() const { return m_Lives; }
	int getScore() const { return m_Score; }

	void setHealth(int health);
	void setLives(int lives);
	void setScore(int score);

private:
	int m_Lives{ 2 };
	int m_Score{ 0 };
	int m_FireTimer{ 0 };
	int m_HurtTimer{ 100 };
	int m_Health{ 3 };
	int m_Dx{ 0 };
	Orb* m_BlowingOrb{nullptr};
};