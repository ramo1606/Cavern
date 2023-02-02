#include "Robot.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Bolt.h"

#include <random>

Robot::Robot(Vector2 pos, ROBOT_TYPE type) : GravityActor(pos), m_Type(type)
{
	m_Speed = GetRandomValue(1, 3);
}

void Robot::update()
{
	GravityActor::update();

	m_ChangeDirTimer -= 1;
	m_FireTimer += 1;

	// Move in current direction - turn around if we hit a wall
	if (move(m_DirectionX, 0, m_Speed)) 
	{
		m_ChangeDirTimer = 0;
	}

	if (m_ChangeDirTimer <= 0) 
	{
		/*
		* Randomly choose a direction to move in
        * If there's a player, there's a two thirds chance that we'll move towards them
		*/
		std::vector<int> directions = { -1, 1 };
		Player* gamePlayer = Game::getInstance()->getPlayer();
		if (gamePlayer) 
		{
			directions.push_back(std::signbit(gamePlayer->getPosition().x - m_Pos.x) ? -1 : 1);
		}
		m_DirectionX = directions[GetRandomValue(0, directions.size()-1)];
		m_ChangeDirTimer = GetRandomValue(100, 250);
	}

	// The more powerful type of robot can deliberately shoot at orbs - turning to face them if necessary
	if (m_Type == ROBOT_TYPE::AGRESSIVE && m_FireTimer >= 24) 
	{
		// Go through all orbs to see if any can be shot at
		for (auto orb : Game::getInstance()->getOrbs()) 
		{
			// The orb must be at our height, and within 200 pixels on the x axis
			if (orb->getPosition().y >= top() && orb->getPosition().y < bottom() && std::abs(orb->getPosition().x - m_Pos.x) < 200)
			{
				m_DirectionX = std::signbit(orb->getPosition().x - m_Pos.x) ? -1 : 1;
				m_FireTimer = 0;
				break;
			}
		}
	}

	// Check to see if we can fire at player
	if (m_FireTimer >= 12) 
	{
		// Random chance of firing each frame. Likelihood increases 10 times if player is at the same height as us
		float fireProbability = Game::getInstance()->fireProbability();
		Player* player = Game::getInstance()->getPlayer();
		if (player) 
		{
			if (top() < player->bottom() && bottom() > player->top())
			{
				fireProbability *= 10;
			}
		}

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dist(0, 1);
		if(dist(gen) < fireProbability)
		{
			m_FireTimer = 0;
			Game::getInstance()->playSound(std::string("laser"), 4);
		}
	}
	else if (m_FireTimer == 8) 
	{
		// Once the fire timer has been set to 0, it will count up - frame 8 of the animation is when the actual bolt is fired
		Game::getInstance()->addBolt({ m_Pos.x + m_DirectionX * 20, m_Pos.y }, m_DirectionX);
	}

	// Am I colliding with an orb? If so, become trapped by it
	for (auto orb : Game::getInstance()->getOrbs())
	{
		if (orb->getTrappedEnemyType() == ROBOT_TYPE::NONE && CheckCollisionPointRec(orb->getPosition(), getActorRectangle()))
		{
			m_Alive = false;
			orb->setFloating(true);
 			orb->setTrappedEnemyType(m_Type);
			Game::getInstance()->playSound(std::string("trap", 4));
			break;
		}
	}

	// Choose and set sprite image
	std::string directionIndex = m_DirectionX > 0 ? std::to_string(1) : std::to_string(0);
	std::string image = std::string("robot") + std::to_string(static_cast<int>(m_Type)) + directionIndex;
	if (m_FireTimer < 12) 
	{
		image += std::to_string(5 + (m_FireTimer / 4));
	}
	else 
	{
		image += std::to_string(1 + ((Game::getInstance()->getTimer() / 4) % 4));
	}
	setImage(*ResourceManager::getSprite(image), true);
}
