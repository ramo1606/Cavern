#include "Game.h"
#include "ResourceManager.h"

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

std::shared_ptr<Game> Game::getInstance(Player& player)
{
	if (!m_Instance)
		m_Instance.reset(new Game(&player));
	return m_Instance;
}

Game::~Game()
{
}

void Game::update()
{
	m_Timer += 1;
}

void Game::draw()
{
}

void Game::reset(int players)
{
}

void Game::nextLevel()
{
	m_LevelColour = (m_LevelColour + 1) % 4;
	m_Level += 1;

	m_Grid = std::vector<std::string>(Common::LEVELS[m_Level % Common::LEVELS.size()]);
	m_Grid.push_back(m_Grid[0]);

	m_Timer = -1;
}

void Game::playSound(Common::ECAVERN_SOUNDS sound, bool isMenu)
{
	if (m_Player || isMenu)
	{
		PlaySound(*ResourceManager::getSound(sound));
	}
}

const std::string& Game::getGrid(int row)
{
	return m_Grid[row];
}


bool Game::block(int x, int y)
{
	// Is there a level grid block at these coordinates ?
	int grid_x = (x - LEVEL_X_OFFSET);
	int grid_y = y;
	if (grid_y > 0 && grid_y < NUM_ROWS)
	{
		auto row = getInstance()->getGrid(grid_y);
		return grid_x >= 0 && grid_x < NUM_COLUMNS&& row.size() > 0 && row[grid_x] != ' ';
	}
	else
	{
		return false;
	}
}