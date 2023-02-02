#include "GravityActor.h"

GravityActor::GravityActor(Vector2 pos, Texture2D* image) : CollideActor(pos, image)
{
}

void GravityActor::update(bool detect)
{
	CollideActor::update();

	// Apply gravity, without going over the maximum fall speed
	m_VelY = std::fmin(m_VelY + 1.f, MAX_FALL_SPEED);

	/*
	* The detect parameter indicates whether we should check for collisions with blocks as we fall. Normally we
    + want this to be the case - hence why this parameter is optional, and is True by default. If the player is
    + in the process of losing a life, however, we want them to just fall out of the level, so False is passed
    + in this case.
	*/
	if (detect) 
	{
		// Move vertically in the appropriate direction, at the appropriate speed
		if (move(0, std::signbit(m_VelY) ? -1 : 1, std::fabs(m_VelY))) 
		{
			/*
			* If move returned True, we must have landed on a block.
			* Note that move doesn't apply any collision detection when the player is moving up - only down
			*/
			m_VelY = 0.f;
			m_Landed = true;
		}
		if (top() >= Common::HEIGHT)
		{
			// Fallen off bottom - reappear at top
			m_Pos.y = 1;
		}
	}
	else 
	{
		// Collision detection disabled - just update the Y coordinate without any further checks
		m_Pos.y += m_VelY;
	}
}
