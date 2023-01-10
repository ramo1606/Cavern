#pragma once
#include <memory>
#include <map>

#include "raylib.h"
#include "Common.h"

using namespace Common;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	bool loadResources();
	static Texture2D* getSprite(ECAVERN_SPRITES obj);
	static Sound* getSound(ECAVERN_SOUNDS obj);
	static Music* getMusic(ECAVERN_MUSIC obj);
	void cleanup();

private:
	static ResourceManager* m_Instance;
	std::map<ECAVERN_SPRITES, Texture2D> m_SpritesMap;
	std::map<ECAVERN_SOUNDS, Sound> m_SoundsMap;
	std::map<ECAVERN_MUSIC, Music> m_MusicMap;
};