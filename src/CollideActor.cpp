#include "CollideActor.h"
#include "Game.h"

CollideActor::CollideActor(Vector2 pos, Texture2D* image) : Actor("CollideActor", pos, image)
{
}

bool CollideActor::move(int dx, int dy, int speed)
{
	bool collision = false;
	int newX = static_cast<int>(m_Pos.x);
	int newY = static_cast<int>(m_Pos.y);

	for (int i = 0; i < speed; ++i) 
	{
		newX = newX + dx;
		newY = newY + dy;

		if (newX < 70 || newX > 730)
			collision = true;

		if ((dy > 0 && newY % Common::GRID_BLOCK_SIZE == 0 ||
			dx > 0 && newX % Common::GRID_BLOCK_SIZE == 0 ||
			dx < 0 && newX % Common::GRID_BLOCK_SIZE == Common::GRID_BLOCK_SIZE - 1)
			&& Game::block(newX, newY)) 
		{
			collision = true;
		}

		m_Pos.x = static_cast<float>(newX);
		m_Pos.y = static_cast<float>(newY);
	}
	return collision;
}
