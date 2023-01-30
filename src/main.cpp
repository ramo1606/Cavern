#include "raylib.h"
#include "Actor.h"
#include "Common.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Player.h"

using namespace Common;

std::map<std::string, int> IMAGE_WIDTH = { {std::string("life"),44}, {std::string("plus"), 40}, {std::string("health"), 40} };

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
            if (m_Game->getPlayer()->getLives() < 0)
            {
                m_Game->playSound(std::string("over"));
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
            drawStatus();
            break;
        case State::GAME_OVER:
            drawStatus();
            DrawTexture(*ResourceManager::getSprite(std::string("over")), 0, 0, WHITE);
            break;
        default:
            break;
        }

        EndDrawing();
    }

    void drawStatus()
    {
        int numberWidth = CHAR_WIDTH[0];
        std::string score = std::to_string(m_Game->getPlayer()->getScore());
        drawText(score, 451, WIDTH - 2 - (numberWidth * score.length()));

        drawText(std::string("LEVEL ") + std::to_string(m_Game->getLevel() + 1), 451);

        std::vector<std::string> healthImages = {};

        for (int i = 0; i < m_Game->getPlayer()->getLives(); ++i) 
        {
            if (i <= 2) 
            {
                healthImages.push_back(std::string("life"));
            }
            if (i > 2) 
            {
                healthImages.push_back(std::string("plus"));
                break;
            }
        }

        if (m_Game->getPlayer()->getLives() >= 0)
        {
            for (int i = 0; i < m_Game->getPlayer()->getHealth(); ++i)
            {
                healthImages.push_back(std::string("health"));
            }
        }

        int x = 0;
        for (int i = 0; i < healthImages.size(); ++i)
        {
            DrawTexture(*ResourceManager::getSprite(healthImages[i]), x, 450, WHITE);
            x += IMAGE_WIDTH[healthImages[i]];
        }
    }

    void drawText(std::string& text, int y, int x = -1) 
    {
        int imageX = 0;
        if (x <= -1) 
        {
            int sum = 0;
            for (auto& c : text) 
            {
                sum += charWidth(c);
            }
            imageX = (WIDTH - sum) / 2;
        }

        for (auto& c : text)
        {
            DrawTexture(*ResourceManager::getSprite(std::string("font0") + std::to_string(static_cast<int>(c))), imageX, y, WHITE);
            imageX += charWidth(c);
        }
    }

    int charWidth(char character) 
    {
        int index = std::max(0, character - 65);
        return CHAR_WIDTH[index];
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
