#include "raylib.h"
#include "Actor.h"
#include "Common.h"
#include "ResourceManager.h"
#include "Game.h"

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
        bool space_pressed = false;
        if (IsKeyDown(KEY_SPACE) && !m_SpaceDown)
        {
            space_pressed = true;
        }

        m_SpaceDown = IsKeyDown(KEY_SPACE);

        switch (m_State)
        {
        case State::MENU:
            if (space_pressed)
            {
                m_State = State::PLAY;
            }
            else
            {
                m_Game->update();
            }
            break;
        case State::PLAY:
            //Has anyone won?
            if (space_pressed)
            {
                m_State = State::GAME_OVER;
            }
            else
            {

            }
            break;
        case State::GAME_OVER:
            if (space_pressed)
            {
                //Reset to menu state
                m_State = State::MENU;
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

        switch (m_State)
        {
        case State::MENU:
            {
                DrawTexture(*ResourceManager::getSprite(ECAVERN_SPRITES::TITLE), 0, 0, WHITE);
                int animFrame = std::min(((m_Game->getTimer() + 40) % 160) / 4, 9);
                DrawTexture(*ResourceManager::getSprite(title_animation[animFrame]), 130, 280, WHITE);
                break;
            }
        case State::PLAY:
            break;
        case State::GAME_OVER:
            DrawTexture(*ResourceManager::getSprite(ECAVERN_SPRITES::OVER), 0, 0, WHITE);
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

    ECAVERN_SPRITES title_animation[10] = { ECAVERN_SPRITES::SPACE_0,
                                            ECAVERN_SPRITES::SPACE_1,
                                            ECAVERN_SPRITES::SPACE_2,
                                            ECAVERN_SPRITES::SPACE_3,
                                            ECAVERN_SPRITES::SPACE_4,
                                            ECAVERN_SPRITES::SPACE_5,
                                            ECAVERN_SPRITES::SPACE_6,
                                            ECAVERN_SPRITES::SPACE_7,
                                            ECAVERN_SPRITES::SPACE_8,
                                            ECAVERN_SPRITES::SPACE_9 };
};


int main(void)
{
    InitWindow(WIDTH, HEIGHT, TITLE.c_str());
    InitAudioDevice();
    SetTargetFPS(60);

    ResourceManager resourceManager;
    resourceManager.loadResources();

    Cavern cavern;

    PlayMusicStream(*ResourceManager::getMusic(ECAVERN_MUSIC::THEME));
    SetMusicVolume(*ResourceManager::getMusic(ECAVERN_MUSIC::THEME), 0.5f);

    while (!WindowShouldClose())
    {
        UpdateMusicStream(*ResourceManager::getMusic(ECAVERN_MUSIC::THEME));
        cavern.update();
        cavern.draw();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
