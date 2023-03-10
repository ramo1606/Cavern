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
	
	// Update all objects
	if (m_Player) 
	{
		m_Player->update();
	}

	for (int i = 0; i < m_Fruits.size(); i++) 
	{
		m_Fruits[i]->update();
	}

	for (int i = 0; i < m_Enemies.size(); i++)
	{
		m_Enemies[i]->update();
	}

	for (int i = 0; i < m_Bolts.size(); i++)
	{
		m_Bolts[i]->update();
	}

	for (int i = 0; i < m_Orbs.size(); i++)
	{
		m_Orbs[i]->update();
	}

	for (int i = 0; i < m_Pops.size(); i++)
	{
		m_Pops[i]->update();
	}

	//Rremove objects which are no longer wanted from the lists and free memory
	auto fruitIt = m_Fruits.begin();
	while (fruitIt != m_Fruits.end())
	{
		Fruit* fruit = *fruitIt;
		if (fruit->isDead())
		{
			fruit->~Fruit();
			ObjPoolFree(&m_FruitsPool, fruit);
			fruit = nullptr;
			fruitIt = m_Fruits.erase(fruitIt);
		}
		else {
			++fruitIt;
		}
	}

	auto enemyIt = m_Enemies.begin();
	while (enemyIt != m_Enemies.end())
	{
		Robot* enemy = *enemyIt;
		if (!enemy->isAlive())
		{
			enemy->~Robot();
			ObjPoolFree(&m_EnemiesPool, enemy);
			enemy = nullptr;
			enemyIt = m_Enemies.erase(enemyIt);
		}
		else {
			++enemyIt;
		}
	}

	auto boltsIt = m_Bolts.begin();
	while (boltsIt != m_Bolts.end())
	{
		Bolt* bolt = *boltsIt;
		if (!bolt->isActive())
		{
			bolt->~Bolt();
			ObjPoolFree(&m_BoltsPool, bolt);
			bolt = nullptr;
			boltsIt = m_Bolts.erase(boltsIt);
		}
		else {
			++boltsIt;
		}
	}

	auto orbsIt = m_Orbs.begin();
	while (orbsIt != m_Orbs.end())
	{
		Orb* orb = *orbsIt;
		if (orb->getTimer() > 250 || orb->getPosition().y < -40)
		{
			orb->~Orb();
			ObjPoolFree(&m_OrbsPool, orb);
			orb = nullptr;
			orbsIt = m_Orbs.erase(orbsIt);
		}
		else {
			++orbsIt;
		}
	}

	auto popsIt = m_Pops.begin();
	while (popsIt != m_Pops.end())
	{
		Pop* pop = *popsIt;
		if (!pop->isAlive())
		{
			pop->~Pop();
			ObjPoolFree(&m_PopsPool, pop);
			pop = nullptr;
			popsIt = m_Pops.erase(popsIt);
		}
		else {
			++popsIt;
		}
	}

	// Every 100 frames, create a random fruit (unless there are no remaining enemies on this level)
	if (m_Timer % 100 == 0 && m_PendingEnemies.size() + m_Enemies.size() > 0) 
	{
		// Create fruit at random position
		addFruit({ static_cast<float>(GetRandomValue(70, 730)), static_cast<float>(GetRandomValue(75, 400)) });
	}

	/*
	* Every 81 frames, if there is at least 1 pending enemy, and the number of active enemies is below the current
    * level's maximum enemies, create a robot
	*/
	if (m_Timer % 81 == 0 && m_PendingEnemies.size() > 0 && m_Enemies.size() < maxEnemies())
	{
		// Retrieve and remove the last element from the pending enemies list
		ROBOT_TYPE robotType = m_PendingEnemies.back();
		Vector2 position = { getRobotSpawnX(), -30 };

		Robot* newEnemy = static_cast<Robot*>(ObjPoolAlloc(&m_EnemiesPool));
		new(newEnemy) Robot(position, robotType);
		
		m_Enemies.push_back(newEnemy);
		m_PendingEnemies.pop_back();
	}

	/*
	* End level if there are no enemies remaining to be created, no existing enemies, no fruit, no popping orbs,
    * and no orbs containing trapped enemies. (We don't want to include orbs which don't contain trapped enemies,
    * as the level would never end if the player kept firing new orbs)
	*/
	if (m_PendingEnemies.size() + m_Enemies.size() + m_Pops.size() == 0)
	{
		int counter = 0;
		for (int i = 0; i < m_Orbs.size(); i++)
		{
			if (m_Orbs[i]->getTrappedEnemyType() != ROBOT_TYPE::NONE)
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
	// Draw appropriate background for this level
	DrawTexture(*ResourceManager::getSprite(std::string("bg") + std::to_string(m_LevelColour)), 0, 0, WHITE);

	std::string blockSprite = "block" + std::to_string(m_LevelColour);

	// Display blocks
	for (int row_y = 0; row_y < NUM_ROWS; ++row_y) 
	{
		auto row = m_Grid[row_y];
		if (row.size() > 0) 
		{
			// Initial offset - large blocks at edge of level are 50 pixels wide
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

	// Draw all objects
	if (m_Player)
	{
		m_Player->draw();
	}

	for (auto& fruit : m_Fruits)
	{
		fruit->draw();
	}

	for (auto& enemy : m_Enemies)
	{
		enemy->draw();
	}

	for (auto& bolt : m_Bolts)
	{
		bolt->draw();
	}

	for (auto& orb : m_Orbs)
	{
		orb->draw();
	}

	for (auto& pop : m_Pops)
	{
		pop->draw();
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

	//clear memory
	auto fruitIt = m_Fruits.begin();
	while (fruitIt != m_Fruits.end())
	{
		Fruit* fruit = *fruitIt;
		fruit->~Fruit();
		ObjPoolCleanUp(&m_FruitsPool, (void**)&fruit);
		++fruitIt;
	}

	auto enemyIt = m_Enemies.begin();
	while (enemyIt != m_Enemies.end())
	{
		Robot* enemy = *enemyIt;
		enemy->~Robot();
		ObjPoolCleanUp(&m_EnemiesPool, (void**)&enemy);
		++enemyIt;
	}

	auto boltsIt = m_Bolts.begin();
	while (boltsIt != m_Bolts.end())
	{
		Bolt* bolt = *boltsIt;
		bolt->~Bolt();
		ObjPoolCleanUp(&m_BoltsPool, (void**)&bolt);
		++boltsIt;
	}

	auto orbsIt = m_Orbs.begin();
	while (orbsIt != m_Orbs.end())
	{
		Orb* orb = *orbsIt;
		orb->~Orb();
		ObjPoolCleanUp(&m_OrbsPool, (void**)&orb);
		++orbsIt;
	}

	auto popsIt = m_Pops.begin();
	while (popsIt != m_Pops.end())
	{
		Pop* pop = *popsIt;
		pop->~Pop();
		ObjPoolCleanUp(&m_PopsPool, (void**)&pop);
		++popsIt;
	}

	//clear containers
	m_Fruits.clear();
	m_Enemies.clear();
	m_Pops.clear();
	m_Orbs.clear();
	m_Bolts.clear();
	m_PendingEnemies.clear();
	
	nextLevel();
}

void Game::nextLevel()
{
	m_Grid.clear();
	m_LevelColour = (m_LevelColour + 1) % 4;
	m_Level += 1;

	// Set up grid
	m_Grid = std::vector<std::string>(Common::LEVELS[m_Level % Common::LEVELS.size()]);
	m_Grid.push_back(m_Grid[0]);

	m_Timer = -1;
	if (m_Player) 
	{
		m_Player->reset();
	}

	/*
	* Each time we change levels we need to cleanup enemies and fruit ObjPool otherwise
	* we will carry fruits in the ObjPool, and after a few levels the pool will be full.
	*/
	auto fruitIt = m_Fruits.begin();
	while (fruitIt != m_Fruits.end())
	{
		Fruit* fruit = *fruitIt;
		fruit->~Fruit();
		ObjPoolCleanUp(&m_FruitsPool, (void**)&fruit);
		++fruitIt;
	}

	auto enemyIt = m_Enemies.begin();
	while (enemyIt != m_Enemies.end())
	{
		Robot* enemy = *enemyIt;
		enemy->~Robot();
		ObjPoolCleanUp(&m_EnemiesPool, (void**)&enemy);
		++enemyIt;
	}

	m_Fruits.clear();
	m_Enemies.clear();

	/*
	* At the start of each level we create a list of pending enemies - enemies to be created as the level plays out.
    * When this list is empty, we have no more enemies left to create, and the level will end once we have destroyed
    * all enemies currently on-screen. Each element of the list will be either NORMAL or AGRESSIVE, where NORMAL corresponds to
    * a standard enemy, and AGRESSIVE is a more powerful enemy.
    * First we work out how many total enemies and how many of each type to create
	*/
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

	// Finally we shuffle the list so that the order is randomised
	auto rd = std::random_device{};
	auto rng = std::default_random_engine{ rd() };
	std::shuffle(std::begin(m_PendingEnemies), std::end(m_PendingEnemies), rng);

	playSound(std::string("level"), 1);
}

void Game::playSound(std::string& sound, int count)
{
	/*
	* Some sounds have multiple varieties. If count > 1, we'll randomly choose one from those
    * We don't play any sounds if there is no player (e.g. if we're on the menu)
	*/
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

// Has the space bar just been pressed? i.e. gone from not being pressed, to being pressed
bool Game::spacePressed()
{
	bool returnValue = false;
	if (IsKeyDown(KEY_SPACE) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
	{
		// Space wasn't down previous frame, but now is
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
	// Likelihood per frame of each robot firing a bolt - they fire more often on higher levels
	return 0.001f + (0.0001f * std::min(100, m_Level));
}

int Game::maxEnemies()
{
	// Maximum number of enemies on-screen at once - increases as you progress through the levels
	return std::min((m_Level + 6) / 2, 8);
}

int Game::getRobotSpawnX()
{
	/*
	* Find a spawn location for a robot, by checking the top row of the grid for empty spots
    * Start by choosing a random grid column
	*/
	int r = GetRandomValue(0, NUM_COLUMNS - 1);

	for (int i = 0; i < NUM_COLUMNS; ++i) 
	{
		/*
		* Keep looking at successive columns (wrapping round if we go off the right-hand side) until
        * we find one where the top grid column is unoccupied
		*/
		int gridX = (r + i) % NUM_COLUMNS;
		if (m_Grid[0][gridX] == ' ')
		{
			return GRID_BLOCK_SIZE * gridX + LEVEL_X_OFFSET + 12;
		}
	}

	/*
	* If we failed to find an opening in the top grid row (shouldn't ever happen), just spawn the enemy
    * in the centre of the screen
	*/
	return WIDTH * 0.5;
}

void Game::addPop(Vector2 pos, POP_TYPE type)
{
	//Allocate new pop in PopsPool
	Pop* newPop = static_cast<Pop*>(ObjPoolAlloc(&m_PopsPool));
	new(newPop) Pop(pos, type);

	//Add reference of pop to vector
	m_Pops.push_back(newPop);
}

void Game::addBolt(Vector2 pos, float dirX)
{
	//Allocate new Bolt in BoltsPool
	Bolt* newBolt = static_cast<Bolt*>(ObjPoolAlloc(&m_BoltsPool));
	new(newBolt) Bolt(pos, dirX);

	//Add reference of bolt to vector
	m_Bolts.push_back(newBolt);
}

void Game::addOrbs(Vector2 pos, float dirX)
{
	//Allocate new Orb in OrbsPool
	Orb* newOrb = static_cast<Orb*>(ObjPoolAlloc(&m_OrbsPool));
	new(newOrb) Orb(pos, dirX);

	//Add reference of orb to vector
	m_Orbs.push_back(newOrb);
}

void Game::addFruit(Vector2 pos, ROBOT_TYPE trapped_enemy_type)
{
	//Allocate new fruit in FruitsPool
	Fruit* newFruit = static_cast<Fruit*>(ObjPoolAlloc(&m_FruitsPool));
	new(newFruit) Fruit(pos, trapped_enemy_type);

	//Add reference of fruit to vector
	m_Fruits.push_back(newFruit);
}
