#include "Actor.h"

Actor::Actor(std::string name, Vector2 pos, Texture2D* image)
	: m_Name(name),
	  m_Pos(pos),
	  m_Image(image)
{
	if (m_Image) 
	{
		m_ImageRectangle = { m_Pos.x, m_Pos.y, static_cast<float>(m_Image->width), static_cast<float>(m_Image->height) };
	}
}

void Actor::setImage(Texture2D& image)
{
	m_Image = &image;
	if (m_Image->width > m_ImageRectangle.width && m_Image->height > m_ImageRectangle.height)
	{
		m_ImageRectangle = { m_Pos.x, m_Pos.y, static_cast<float>(m_Image->width), static_cast<float>(m_Image->height) };
	}
}

void Actor::processInput()
{
}

void Actor::update()
{
}

void Actor::draw()
{
	if (m_Image) 
	{
		DrawTexture(*m_Image, m_Pos.x - m_Image->width * 0.5, m_Pos.y - m_Image->height * 0.5, WHITE);
	}
}

Vector2 Actor::getPosition()
{
	return m_Pos;
}

Rectangle Actor::getImageRectangle()
{
	return m_ImageRectangle;
}
