#include "Game.h"
#include "ResourceManager.h"

#include <cmath>
#include <algorithm>
#include <random>

int Game::m_Timer = -1;
std::shared_ptr<Game> Game::m_Instance = nullptr;

Game::Game(Player* player) : m_Player(player)
{
	nextLevel();
}

std::shared_ptr<Game> Game::getInstance()
{
	if (!m_Instance)
		m_Instance.reset(new Game());
	return m_Instance;
}

Game::~Game()
{
}

void Game::init()
{
	Vector2 pos = { 0, 0 };
	m_Player = std::make_unique<Player>(pos);
	if (m_Player)
	{
		m_Player->reset();
	}
}

void Game::update()
{
	m_Timer += 1;
	
	if (m_Player) 
	{
		m_Player->update();
	}

	for (int i = 0; i < m_Fruits.size(); i++) 
	{
		m_Fruits[i].update();
	}

	for (int i = 0; i < m_Enemies.size(); i++)
	{
		m_Enemies[i].update();
	}

	for (int i = 0; i < m_Bolts.size(); i++)
	{
		m_Bolts[i].update();
	}

	for (int i = 0; i < m_Orbs.size(); i++)
	{
		m_Orbs[i].update();
	}

	for (int i = 0; i < m_Pops.size(); i++)
	{
		m_Pops[i].update();
	}

	auto fruitIt = m_Fruits.begin();
	while (fruitIt != m_Fruits.end())
	{
		if (fruitIt->isDead())
		{
			fruitIt = m_Fruits.erase(fruitIt);
		}
		else {
			++fruitIt;
		}
	}

	auto enemyIt = m_Enemies.begin();
	while (enemyIt != m_Enemies.end())
	{
		if (!enemyIt->isAlive())
		{
			enemyIt = m_Enemies.erase(enemyIt);
		}
		else {
			++enemyIt;
		}
	}

	auto boltsIt = m_Bolts.begin();
	while (boltsIt != m_Bolts.end())
	{
		if (!boltsIt->isActive())
		{
			boltsIt = m_Bolts.erase(boltsIt);
		}
		else {
			++boltsIt;
		}
	}

	auto orbsIt = m_Orbs.begin();
	while (orbsIt != m_Orbs.end())
	{
		if (orbsIt->getTimer() > 250 || orbsIt->getPosition().y < -40)
		{
			orbsIt = m_Orbs.erase(orbsIt);
		}
		else {
			++orbsIt;
		}
	}

	auto popsIt = m_Pops.begin();
	while (popsIt != m_Pops.end())
	{
		if (!popsIt->isAlive())
		{
			popsIt = m_Pops.erase(popsIt);
		}
		else {
			++popsIt;
		}
	}

	if (m_Timer % 100 == 0 && m_PendingEnemies.size() + m_Enemies.size() > 0) 
	{
		m_Fruits.push_back(Fruit({ static_cast<float>(GetRandomValue(70, 730)), static_cast<float>(GetRandomValue(75, 400)) }));
	}

	if (m_Timer % 81 == 0 && m_PendingEnemies.size() > 0 && m_Enemies.size() < maxEnemies())
	{
		ROBOT_TYPE robotType = m_PendingEnemies.back();
		Vector2 position = { getRobotSpawnX(), -30 };
		m_Enemies.push_back(Robot(position, robotType));
		m_PendingEnemies.pop_back();
	}

	if (m_PendingEnemies.size() + m_Enemies.size() + m_Pops.size() == 0)
	{
		int counter = 0;
		for (int i = 0; i < m_Orbs.size(); i++)
		{
			if (m_Orbs[i].getTrappedEnemyType() != ROBOT_TYPE::NONE)
			{
				counter++;
			}
		}
		
		if (counter == 0) 
		{
			nextLevel();
		}
	}
}

void Game::draw()
{
	DrawTexture(*ResourceManager::getSprite(std::string("bg") + std::to_string(m_LevelColour)), 0, 0, WHITE);

	std::string blockSprite = "block" + std::to_string(m_LevelColour);

	for (int row_y = 0; row_y < NUM_ROWS; ++row_y) 
	{
		auto row = m_Grid[row_y];
		if (row.size() > 0) 
		{
			int x = LEVEL_X_OFFSET;
			for (const auto& block : row) 
			{
				if (block != ' ') 
				{
					DrawTexture(*ResourceManager::getSprite(blockSprite), x, row_y * GRID_BLOCK_SIZE, WHITE);
				}
				x += GRID_BLOCK_SIZE;
			}
		}
	}


	if (m_Player)
	{
		m_Player->draw();
	}

	for (auto& fruit : m_Fruits)
	{
		fruit.draw();
	}

	for (auto& enemy : m_Enemies)
	{
		enemy.draw();
	}

	for (auto& bolt : m_Bolts)
	{
		bolt.draw();
	}

	for (auto& orb : m_Orbs)
	{
		orb.draw();
	}

	for (auto& pop : m_Pops)
	{
		pop.draw();
	}
}

Player* Game::getPlayer() const
{
	return m_Player.get();
}

void Game::reset()
{
	Game::m_Timer = -1;
	m_LevelColour = -1;
	m_Level = -1;

	m_SpaceDown = false;
	m_Grid.clear();
	m_Player.reset();
	m_Player = nullptr;

	nextLevel();
}

void Game::nextLevel()
{
	m_Grid.clear();
	m_LevelColour = (m_LevelColour + 1) % 4;
	m_Level += 1;

	m_Grid = std::vector<std::string>(Common::LEVELS[m_Level % Common::LEVELS.size()]);
	m_Grid.push_back(m_Grid[0]);

	m_Timer = -1;
	if (m_Player) 
	{
		m_Player->reset();
	}

	m_Fruits.clear();
	m_Enemies.clear();

	int numEnemies = 10 + m_Level;
	int numStrongEnemies = 1 + static_cast<int>(m_Level / 1.5f);
	int numWeakEnemies = numEnemies - numStrongEnemies;

	for (int i = 0; i < numStrongEnemies; i++) 
	{
		m_PendingEnemies.push_back(ROBOT_TYPE::AGRESSIVE);
	}
	for (int i = 0; i < numWeakEnemies; i++)
	{
		m_PendingEnemies.push_back(ROBOT_TYPE::NORMAL);
	}

	auto rd = std::random_device{};
	auto rng = std::default_random_engine{ rd() };
	std::shuffle(std::begin(m_PendingEnemies), std::end(m_PendingEnemies), rng);

	playSound(std::string("level"), 1);
}

void Game::playSound(std::string& sound, int count)
{
	if (m_Player)
	{
		PlaySound(*ResourceManager::getSound(sound + std::to_string(GetRandomValue(0, count - 1))));
	}
}

const std::string& Game::getGrid(int row)
{
	return m_Grid[row];
}


bool Game::block(int x, int y)
{
	// Is there a level grid block at these coordinates ?
	int grid_x = (x - LEVEL_X_OFFSET) / GRID_BLOCK_SIZE;
	int grid_y = y / GRID_BLOCK_SIZE;
	if (grid_y > 0 && grid_y < NUM_ROWS)
	{
		auto row = getInstance()->getGrid(grid_y);
		return grid_x >= 0 && grid_x < NUM_COLUMNS && row.size() > 0 && row[grid_x] != ' ';
	}
	else
	{
		return false;
	}
}

bool Game::spacePressed()
{
	bool returnValue = false;
	if (IsKeyDown(KEY_SPACE) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
	{
		if (!m_SpaceDown)
		{
			m_SpaceDown = true;
			returnValue = true;
		}
	}
	else
	{
		m_SpaceDown = false;
	}

	return returnValue;
}

float Game::fireProbability()
{
	return 0.001f + (0.0001f * std::min(100, m_Level));
}

int Game::maxEnemies()
{
	return std::min((m_Level + 6) / 2, 8);
}

int Game::getRobotSpawnX()
{
	int r = GetRandomValue(0, NUM_COLUMNS - 1);

	for (int i = 0; i < NUM_COLUMNS; ++i) 
	{
		int gridX = (r + i) % NUM_COLUMNS;
		if (m_Grid[0][gridX] == ' ')
		{
			return GRID_BLOCK_SIZE * gridX + LEVEL_X_OFFSET + 12;
		}
	}

	return WIDTH * 0.5;
}

void Game::addPop(Pop&& pop)
{
	m_Pops.push_back(pop);
}

void Game::addFruit(Fruit&& fruit)
{
	m_Fruits.push_back(fruit);
}
