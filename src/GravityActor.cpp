#include "GravityActor.h"

GravityActor::GravityActor(Vector2 pos, Texture2D* image) : CollideActor(pos, image)
{
}

void GravityActor::update(bool detect)
{
	m_VelY = std::fmin(m_VelY + 1.f, MAX_FALL_SPEED);

	if (detect) 
	{
		if (move(0, std::signbit(m_VelY), std::fabs(m_VelY))) 
		{
			m_VelY = 0.f;
			m_Landed = true;
		}
		if (m_Pos.y >= Common::HEIGHT) 
		{
			m_Pos.y = 1;
		}
	}
	else 
	{
		m_Pos.y += m_VelY;
	}
}
