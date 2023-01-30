#include "Pop.h"
#include "ResourceManager.h"

Pop::Pop(Vector2 pos, POP_TYPE type) : Actor("Blank", pos), m_Type(type)
{
}

void Pop::update()
{
	m_Timer += 1;
	std::string popImage = std::string("pop") + std::to_string(static_cast<int>(m_Type)) + std::to_string(static_cast<int>(m_Timer * 0.5));
	setImage(*ResourceManager::getSprite(popImage));
}
