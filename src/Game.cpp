#include "Game.h"
#include "ResourceManager.h"

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
}

void Game::playSound(std::string& sound, bool isMenu)
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
	if (IsKeyDown(KEY_SPACE)) 
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
