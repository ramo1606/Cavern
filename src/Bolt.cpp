#define RMEM_IMPLEMENTATION
#include "Bolt.h"
#include "Orb.h"
#include "Game.h"
#include "ResourceManager.h"

Bolt::Bolt(Vector2 pos, float dirX) : CollideActor(pos)
{
	m_DirectionX = dirX;
}

void Bolt::update()
{
	// Move horizontally and check to see if we've collided with a block
	if (move(m_DirectionX, 0, BOLT_SPEED))
	{
		// Collided
		m_Active = false;
	}
	else 
	{
		// We didn't collide with a block - check to see if we collided with an orb or the player
		for (Orb* orb : Game::getInstance()->getOrbs()) 
		{
			if (orb->hitTest(*this)) 
			{
				m_Active = false;
				break;
			}
		}

		if (m_Active && Game::getInstance()->getPlayer())
		{
			if (Game::getInstance()->getPlayer()->hitTest(*this))
			{
				m_Active = false;
			}
		}
	}

	std::string directionIndex = m_DirectionX > 0 ? std::to_string(1) : std::to_string(0);
	std::string animFrame = std::to_string((Game::getInstance()->getTimer() / 4) % 2);
	setImage(*ResourceManager::getSprite(std::string("bolt") + directionIndex + animFrame), true);
}