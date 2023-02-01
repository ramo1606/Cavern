#pragma once
#include <string>
#include <unordered_map>
#include <raylib.h>

#include "Common.h"

struct ActorSize 
{
	int width{ 0 };
	int height{ 0 };
};

using ActorSize = struct ActorSize;

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