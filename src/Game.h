#pragma once
#include <vector>
#include <memory>
#include <string> 

#include "Common.h"
#include "Player.h"
#include "Fruit.h"

using namespace Common;

class Game
{
public:
	~Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	static std::shared_ptr<Game> getInstance();

	void init();
	void update();
	void draw();

	Player* getPlayer() const;

	void reset();

	void nextLevel();
	void playSound(std::string& sound, bool isMenu = false);

	static int getTimer() { return m_Timer; }
	const std::string& getGrid(int row);
	static bool block(int x, int y);

	bool spacePressed();

private:
	Game(Player* player = nullptr);
	static std::shared_ptr<Game> m_Instance;

	static int m_Timer;
	int m_LevelColour{ -1 };
	int m_Level{ -1 };

	std::vector<std::string> m_Grid{};
	std::unique_ptr<Player> m_Player = nullptr;

	std::vector<Fruit> m_Fruits{};

	bool m_SpaceDown{ false };
};