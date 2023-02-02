#pragma once
#include "GravityActor.h"

class Orb;

/*
* Player class model the main character that we are going to control
*/
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
	int m_HurtTimer{ 100 };		// Invulnerable for this many frames
	int m_Health{ 3 };
	int m_Dx{ 0 };				// -1 = left, 1 = right
	Orb* m_BlowingOrb{nullptr};
};