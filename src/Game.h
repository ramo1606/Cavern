#pragma once
#include <vector>
#include <memory>
#include <string> 

#include "Common.h"
#include "Player.h"
#include "Fruit.h"
#include "Robot.h"
#include "Pop.h"
#include "Orb.h"
#include "Bolt.h"

#include "rmem.h"

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
	void playSound(std::string& sound, int count = 1);

	int getLevel() { return m_Level; }
	static int getTimer() { return m_Timer; }
	const std::string& getGrid(int row);
	static bool block(int x, int y);

	bool spacePressed();
	float fireProbability();
	int maxEnemies();
	int getRobotSpawnX();

	void addPop(Vector2 pos, POP_TYPE type = POP_TYPE::FRUIT);
	void addBolt(Vector2 pos, float dirX);
	void addOrbs(Vector2 pos, float dirX);
	void addFruit(Vector2 pos, ROBOT_TYPE trapped_enemy_type = ROBOT_TYPE::NORMAL);

	std::vector<Orb*>& getOrbs() { return m_Orbs; }
	std::vector<Bolt*>& getBolts() { return m_Bolts; }

private:
	Game(Player* player = nullptr);
	static std::shared_ptr<Game> m_Instance;

	static int m_Timer;
	int m_LevelColour{ -1 };
	int m_Level{ -1 };

	std::vector<std::string> m_Grid{};
	std::unique_ptr<Player> m_Player = nullptr;

	std::vector<Fruit*> m_Fruits{};
	std::vector<Robot*> m_Enemies{};
	std::vector<Pop*> m_Pops{};
	std::vector<Orb*> m_Orbs{};
	std::vector<Bolt*> m_Bolts{};
	std::vector<ROBOT_TYPE> m_PendingEnemies{};

	ObjPool m_FruitsPool = CreateObjPool(sizeof(Fruit), 25);
	ObjPool m_EnemiesPool = CreateObjPool(sizeof(Robot), 25);
	ObjPool m_PopsPool = CreateObjPool(sizeof(Pop), 25);
	ObjPool m_OrbsPool = CreateObjPool(sizeof(Orb), 10);
	ObjPool m_BoltsPool = CreateObjPool(sizeof(Bolt), 40);

	bool m_SpaceDown{ false };
};