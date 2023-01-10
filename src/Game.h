#pragma once
#include <vector>
#include <memory>
#include <string> 

#include "Common.h"

class Player;

class Game
{
public:
	~Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	static std::shared_ptr<Game> getInstance();
	static std::shared_ptr<Game> getInstance(Player& player);

	void update();
	void draw();

	void reset(int players);

	void nextLevel();
	void playSound(Common::ECAVERN_SOUNDS sound, bool isMenu = false);

	int getTimer() { return m_Timer; }
	const std::string& getGrid(int row);
	static bool block(int x, int y);

private:
	Game(Player* player = nullptr);
	static std::shared_ptr<Game> m_Instance;

	int m_Timer{ -1 };
	int m_LevelColour{ -1 };
	int m_Level{ -1 };

	std::vector<std::string> m_Grid{};
	Player* m_Player = nullptr;
};