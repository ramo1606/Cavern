#include "Fruit.h"
#include "Game.h"
#include "ResourceManager.h"

Fruit::Fruit(Vector2 pos, ROBOT_TYPE trapped_enemy_type) : GravityActor(pos)
{
	if (trapped_enemy_type == ROBOT_TYPE::NORMAL) 
	{
		int select = GetRandomValue(0, 2);
		FRUIT_TYPE selection[3] = {FRUIT_TYPE::APPLE, FRUIT_TYPE::RASPBERRY, FRUIT_TYPE::LEMON};
		m_Type = selection[select];
	}
	else 
	{
		std::vector<FRUIT_TYPE> selection = {};
		for (int i = 0; i < 10; ++i) 
		{
			selection.push_back(FRUIT_TYPE::APPLE);
			selection.push_back(FRUIT_TYPE::RASPBERRY);
			selection.push_back(FRUIT_TYPE::LEMON);
		}

		for (int i = 0; i < 9; ++i)
		{
			selection.push_back(FRUIT_TYPE::EXTRA_HEALTH);
		}

		selection.push_back(FRUIT_TYPE::EXTRA_LIFE);
	}
}

void Fruit::update()
{
	GravityActor::update();

	Player* gamePlayer = Game::getInstance()->getPlayer();
	if (gamePlayer && CheckCollisionPointRec(getPosition(), gamePlayer->getImageRectangle()))
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
			Game::getInstance()->playSound(std::string("score0"));
			break;
		}
		m_TimeToLive = 0;
	}
	else 
	{
		m_TimeToLive -= 1;
	}

	if(m_TimeToLive <= 0) 
	{
		// Create 'pop' animation
		//Game::getInstance()
	}

	std::string frames[4] = { std::to_string(0), std::to_string(1) , std::to_string(2), std::to_string(1) };
	std::string animFrame = frames[(Game::getInstance()->getTimer() / 6) % 4];
	setImage(*ResourceManager::getSprite(std::string("fruit") + std::to_string(static_cast<int>(m_Type)) + animFrame));
}
