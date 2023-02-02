#include "CollideActor.h"
#include "Game.h"
#include "ResourceManager.h"

CollideActor::CollideActor(Vector2 pos, Texture2D* image) : Actor("CollideActor", pos, image)
{
}

void CollideActor::update()
{
	Actor::update();
}

bool CollideActor::move(int dx, int dy, int speed)
{
	int newX = static_cast<int>(m_Pos.x);
	int newY = static_cast<int>(m_Pos.y);

	// Movement is done 1 pixel at a time, which ensures we don't get embedded into a wall we're moving towards
	for (int i = 0; i < speed; ++i) 
	{
		newX += dx;
		newY += dy;

		int actorBottom = newY + static_cast<int>(getActorRectangle().height * 0.5f);
		
		if (newX < 70 || newX > 730)
			return true;

		/*
        * The code below checks to see if we're position we're trying to move into overlaps with a block. We only
        * need to check the direction we're actually moving in. So first, we check to see if we're moving down
        * (dy > 0). If that's the case, we then check to see if the proposed new y coordinate is a multiple of
        * GRID_BLOCK_SIZE. If it is, that means we're directly on top of a place where a block might be. If that's
        * also true, we then check to see if there is actually a block at the given position. If there's a block
        * there, we return True and don't update the object to the new position.
        * For movement to the right, it's the same except we check to ensure that the new x coordinate is a multiple
        * of GRID_BLOCK_SIZE. For moving left, we check to see if the new x coordinate is the last (right-most)
        * pixel of a grid block.
        * Note that we don't check for collisions when the player is moving up.
		*/
		if ((dy > 0 && actorBottom % Common::GRID_BLOCK_SIZE == 0 ||
			dx > 0 && newX % Common::GRID_BLOCK_SIZE == 0 ||
			dx < 0 && newX % Common::GRID_BLOCK_SIZE == Common::GRID_BLOCK_SIZE - 1) &&
			Game::block(newX, actorBottom))
		{
			return true;
		}

		// We only update the object's position if there wasn't a block there.
		m_Pos.x = static_cast<float>(newX);
		m_Pos.y = static_cast<float>(newY);
	}

	//Didn't collide with block or edge of level
	return false;
}
