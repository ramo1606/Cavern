#include "Fruit.h"
#include "Pop.h"
#include "Game.h"
#include "ResourceManager.h"

Fruit::Fruit(Vector2 pos, ROBOT_TYPE trapped_enemy_type) : GravityActor(pos)
{
	// Choose which type of fruit we're going to be.
	if (trapped_enemy_type == ROBOT_TYPE::NORMAL) 
	{
		int select = GetRandomValue(0, 2);
		FRUIT_TYPE selection[3] = {FRUIT_TYPE::APPLE, FRUIT_TYPE::RASPBERRY, FRUIT_TYPE::LEMON};
		m_Type = selection[select];
	}
	else 
	{
		/*
		* If trapped_enemy_type is AGRESSIVE, it means this fruit came from bursting an orb containing the more dangerous type
        * of enemy. In this case there is a chance of getting an extra help or extra life power up
        * We create a list containing the possible types of fruit, in proportions based on the probability we want
        * each type of fruit to be chosen
		*/
		std::vector<FRUIT_TYPE> selection = {};
		for (int i = 0; i < 10; ++i) 
		{
			// Each of these appear in the list 10 times
			selection.push_back(FRUIT_TYPE::APPLE);
			selection.push_back(FRUIT_TYPE::RASPBERRY);
			selection.push_back(FRUIT_TYPE::LEMON);
		}

		for (int i = 0; i < 9; ++i)
		{
			// This appears 9 times
			selection.push_back(FRUIT_TYPE::EXTRA_HEALTH);
		}

		// This only appears once
		selection.push_back(FRUIT_TYPE::EXTRA_LIFE);

		// Randomly choose one from the list
		m_Type = selection[GetRandomValue(0, selection.size() - 1)];
	}
}

void Fruit::update()
{
	GravityActor::update();

	// Does the player exist, and are they colliding with us?
	Player* gamePlayer = Game::getInstance()->getPlayer();
	if (gamePlayer && CheckCollisionPointRec(getPosition(), gamePlayer->getActorRectangle()))
	{
		switch (m_Type)
		{
		case FRUIT_TYPE::EXTRA_HEALTH:
			gamePlayer->setHealth(std::min(3, gamePlayer->getHealth() + 1));
			Game::getInstance()->playSound(std::string("bonus"));
			break;
		case FRUIT_TYPE::EXTRA_LIFE:
			gamePlayer->setLives(gamePlayer->getLives() + 1);
			Game::getInstance()->playSound(std::string("bonus"));
			break;
		default:
			gamePlayer->setScore(gamePlayer->getScore() + (static_cast<int>(m_Type) + 1) * 100);
			Game::getInstance()->playSound(std::string("score"));
			break;
		}
		m_TimeToLive = 0;	// Disappear
	}
	else 
	{
		m_TimeToLive -= 1;
	}

	if(m_TimeToLive <= 0) 
	{
		// Create 'pop' animation
		Game::getInstance()->addPop({ m_Pos.x, m_Pos.y }, POP_TYPE::FRUIT);
	}

	std::string frames[4] = { std::to_string(0), std::to_string(1) , std::to_string(2), std::to_string(1) };
	std::string animFrame = frames[(Game::getInstance()->getTimer() / 6) % 4];
	setImage(*ResourceManager::getSprite(std::string("fruit") + std::to_string(static_cast<int>(m_Type)) + animFrame), true);
}
