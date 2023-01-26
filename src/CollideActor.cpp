#include "CollideActor.h"
#include "Game.h"
#include "ResourceManager.h"

CollideActor::CollideActor(Vector2 pos, Texture2D* image) : Actor("CollideActor", pos, image)
{
}

bool CollideActor::move(int dx, int dy, int speed)
{
	Texture2D* blockTexture = ResourceManager::getSprite(std::string("block0"));
	int newX = static_cast<int>(m_Pos.x);
	int newY = static_cast<int>(m_Pos.y);

	for (int i = 0; i < speed; ++i) 
	{
		newX += dx;
		newY += dy;

		int playerBottom = newY + static_cast<int>(getImageRectangle().height * 0.5);
		
		if (newX < 70 || newX > 730)
			return true;

		if ((dy > 0 && playerBottom % Common::GRID_BLOCK_SIZE == 0 ||
			dx > 0 && newX % Common::GRID_BLOCK_SIZE == 0 ||
			dx < 0 && newX % Common::GRID_BLOCK_SIZE == Common::GRID_BLOCK_SIZE - 1) &&
			Game::block(newX, playerBottom))
		{
			return true;
		}

		m_Pos.x = static_cast<float>(newX);
		m_Pos.y = static_cast<float>(newY);
	}
	return false;
}
