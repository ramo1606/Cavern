#include "Actor.h"

Actor::Actor(std::string name, Vector2 pos, Texture2D* image)
	: m_Name(name),
	  m_Pos(pos),
	  m_Image(image)
{
	if (m_Image) 
	{
		setActorSize();
	}
}

void Actor::setImage(Texture2D& image, bool resizeActor)
{
	m_Image = &image;
	if (resizeActor) 
	{
		setActorSize();
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
		DrawTexture(*m_Image, left(), top(), WHITE);
	}
}

Vector2 Actor::getPosition() const
{
	return m_Pos;
}

Rectangle Actor::getActorRectangle()
{
	return { left(), top(), static_cast<float>(getWidht()), static_cast<float>(getHeight())};
}

int Actor::getWidht()
{
	return m_ActorSize.width;
}

int Actor::getHeight()
{
	return m_ActorSize.height;
}

const std::string& Actor::getName() const
{
	return m_Name;
}

void Actor::setActorSize()
{
	if (m_Image)
	{
		m_ActorSize = { m_Image->width, m_Image->height };
	}
}