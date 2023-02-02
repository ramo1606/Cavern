#pragma once
#include <string>
#include <unordered_map>
#include <raylib.h>

#include "Common.h"

/*
* Actor have a size independent of image, this is because we use a blank image for blink effect,
* this image is smaller and will affect collision detection.
*/
struct ActorSize 
{
	int width{ 0 };
	int height{ 0 };
};

using ActorSize = struct ActorSize;

/*
* Base Actor class, all the elements in the game will derive from this class.
* It contains the position and a pointer to a image that will draw every frame.
*/
class Actor
{
public:
	Actor(std::string name = "", Vector2 pos = { 0, 0 }, Texture2D* image = nullptr);
	Actor(const Actor&) = default;
	Actor& operator=(const Actor&) = default;
	virtual ~Actor() = default;

	virtual void processInput();
	virtual void update();
	virtual void draw();
	
	virtual void setImage(Texture2D& image, bool resizeActor = false);

	Vector2 getPosition() const;
	Rectangle getActorRectangle();
	int getWidht();
	int getHeight();
	const std::string& getName() const;

	//Functions that returns the limits of the actor "collider"
	float top() const { return m_Pos.y - static_cast<float>(m_ActorSize.height) * 0.5f; }
	float bottom() const { return m_Pos.y + static_cast<float>(m_ActorSize.height) * 0.5f; }
	float left() const { return m_Pos.x - static_cast<float>(m_ActorSize.width) * 0.5f; }
	float right() const { return m_Pos.x + static_cast<float>(m_ActorSize.width) * 0.5f; }

protected:
	std::string m_Name{ "" };
	Texture2D* m_Image = nullptr;
	Vector2 m_Pos{ 0, 0 };
	ActorSize m_ActorSize{ 0, 0 };

	void setActorSize();
};