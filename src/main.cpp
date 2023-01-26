#include "raylib.h"
#include "Actor.h"
#include "Common.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Player.h"

using namespace Common;

enum class State : uint8_t
{
    MENU,
    PLAY,
    GAME_OVER
};

class Cavern
{
public:
    Cavern()
    {
        m_Game = Game::getInstance();
    }

    void update()
    {
        switch (m_State)
        {
        case State::MENU:
            if (m_Game->spacePressed())
            {
                m_State = State::PLAY;
                m_Game->init();
            }
            else
            {
                m_Game->update();
            }
            break;
        case State::PLAY:
            //Has anyone won?
            if (m_Game->spacePressed())
            {
                m_State = State::GAME_OVER;
            }
            else
            {
                m_Game->update();
            }
            break;
        case State::GAME_OVER:
            if (m_Game->spacePressed())
            {
                //Reset to menu state
                m_State = State::MENU;
                m_Game->reset();
            }
            break;
        default:
            break;
        }
    }

    void draw()
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        m_Game->draw();

        switch (m_State)
        {
        case State::MENU:
            {
            DrawTexture(*ResourceManager::getSprite(std::string("title")), 0, 0, WHITE);
                int animFrame = std::min(((m_Game->getTimer() + 40) % 160) / 4, 9);
                DrawTexture(*ResourceManager::getSprite(std::string("space") + std::to_string(animFrame)), 130, 280, WHITE);
                break;
            }
        case State::PLAY:
            break;
        case State::GAME_OVER:
            DrawTexture(*ResourceManager::getSprite(std::string("over")), 0, 0, WHITE);
            break;
        default:
            break;
        }

        EndDrawing();
    }
private:
    bool m_SpaceDown{ false };
    State m_State{ State::MENU };
    uint8_t m_NumPlayers{ 1 };
    std::shared_ptr<Game> m_Game = nullptr;
};


int main(void)
{
    InitWindow(WIDTH, HEIGHT, TITLE.c_str());
    InitAudioDevice();
    SetTargetFPS(60);

    ResourceManager resourceManager;
    resourceManager.loadResources();

    Cavern cavern;

    PlayMusicStream(*ResourceManager::getMusic(std::string("theme")));
    SetMusicVolume(*ResourceManager::getMusic(std::string("theme")), 0.5f);

    while (!WindowShouldClose())
    {
        UpdateMusicStream(*ResourceManager::getMusic(std::string("theme")));
        cavern.update();
        cavern.draw();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
