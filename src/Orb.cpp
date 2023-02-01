#include "Orb.h"
#include "Game.h"
#include "ResourceManager.h"

Orb::Orb(Vector2 pos, float dirX) : CollideActor(pos)
{
	m_DirectionX = dirX;
}

void Orb::update()
{
	m_Timer += 1;

	if (m_Floating) 
	{
		move(0, -1, GetRandomValue(1, 2));
	}
	else 
	{
		if (move(m_DirectionX, 0, 4)) 
		{
			m_Floating = true;
		}
	}

	if (m_Timer == m_BlownFrames) 
	{
		m_Floating = true;
	}
	else if (m_Timer >= MAX_TIMER || m_Pos.y <= -40) 
	{
		Game::getInstance()->addPop(m_Pos, POP_TYPE::ENEMY);
		if (m_TrappedEnemyType != ROBOT_TYPE::NONE) 
		{
			Game::getInstance()->addFruit(m_Pos, m_TrappedEnemyType);
		}
		Game::getInstance()->playSound(std::string("pop"), 4);
	}

	std::string image;
	if (m_Timer < 9) 
	{
		image = std::string("orb") + std::to_string(m_Timer / 3);
	}
	else 
	{
		if (m_TrappedEnemyType != ROBOT_TYPE::NONE) 
		{
			image = std::string("trap") + std::to_string(static_cast<int>(m_TrappedEnemyType)) + std::to_string((m_Timer / 4) % 8);
		}
		else 
		{
			image = std::string("orb") + std::to_string((3 + ((m_Timer - 9) / 8) % 4));
		}
	}

	setImage(*ResourceManager::getSprite(image), true);
}

bool Orb::hitTest(Bolt& bolt)
{
	bool collided = CheckCollisionPointRec(bolt.getPosition(), getActorRectangle());
	if(collided)
	{
		m_Timer = MAX_TIMER - 1;
	}
	return collided;
}
