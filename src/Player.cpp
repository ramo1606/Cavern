#include "Player.h"
#include "ResourceManager.h"
#include "Game.h"


Player::Player(Vector2 pos, Texture2D* image) : GravityActor(pos, image)
{
    setImage(*ResourceManager::getSprite(std::string("still")), true);
}

void Player::update()
{
    GravityActor::update(m_Health > 0);

    m_FireTimer -= 1;
    m_HurtTimer -= 1;

    if (m_Landed) 
    {
        m_HurtTimer = std::min(m_HurtTimer, 100);
    }

    if (m_HurtTimer > 100) 
    {
        if (m_Health > 0) 
        {
            move(static_cast<int>(m_DirectionX), 0, 4);
        }
        else 
        {
            if (m_Pos.y >= Common::HEIGHT*1.5) 
            {
                m_Lives -= 1;
                reset();
            }
        }
    }
    else 
    {
        processInput();
    }

    if (IsKeyDown(KEY_SPACE) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
    {
        if (m_BlowingOrb) 
        {
            m_BlowingOrb->setBlownFrames(m_BlowingOrb->getBlownFrames() + 4);
            if (m_BlowingOrb->getBlownFrames() >= 120) 
            {
                m_BlowingOrb = nullptr;
            }
        }
    }
    else 
    {
        m_BlowingOrb = nullptr;
    }

    setImage(*ResourceManager::getSprite(std::string("blank")));

    if (m_HurtTimer <= 0 || m_HurtTimer % 2 == 1) 
    {
        int dirIndex = m_DirectionX > 0 ? 1 : 0;
        if (m_HurtTimer > 100) 
        {
            if (m_Health > 0) 
            {
                setImage(*ResourceManager::getSprite(std::string("recoil") + std::to_string(dirIndex)));
            }
            else
            {
                setImage(*ResourceManager::getSprite(std::string("fall") + std::to_string((Game::getTimer() / 4) % 2)));
            }
        }
        else if (m_FireTimer > 0) 
        {
            setImage(*ResourceManager::getSprite(std::string("blow") + std::to_string(dirIndex)));
        }
        else if (m_Dx == 0)
        {
            setImage(*ResourceManager::getSprite(std::string("still")));
        }
        else 
        {
            int frame = (Game::getTimer() / 8) % 4;
            setImage(*ResourceManager::getSprite(std::string("run") + std::to_string(dirIndex) + std::to_string(frame)));
        }
    }
}

void Player::processInput()
{
    m_Dx = 0;
    if (IsKeyDown(KEY_LEFT) || GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) == -1)
    {
        m_Dx = -1;
    }
    else if (IsKeyDown(KEY_RIGHT) || GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) == 1)
    {
        m_Dx = 1;
    }

    if (m_Dx != 0)
    {
        m_DirectionX = m_Dx;
        
        if (m_FireTimer < 10) 
        {
            move(m_Dx, 0, 4);
        }
    }

    if (Game::getInstance()->spacePressed() && m_FireTimer <= 0 && Game::getInstance()->getOrbs().size() < 5)
    {
        float x = std::min(730, std::max(70, static_cast<int>(m_Pos.x + m_DirectionX * 38)));
        float y = m_Pos.y - 10;

        auto& orbs = Game::getInstance()->getOrbs();
        Game::getInstance()->addOrbs({ x, y }, m_DirectionX);
        m_BlowingOrb = orbs.back();
        Game::getInstance()->playSound(std::string("blow"), 4);
        m_FireTimer = 20;
    }

    if ((IsKeyDown(KEY_UP) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) && m_VelY == 0 && m_Landed)
    {
        m_VelY = -16;
        m_Landed = false;
        Game::getInstance()->playSound(std::string("jump"));
    }
}

void Player::reset()
{
    m_Pos = { Common::WIDTH * 0.5, 100 };
    m_VelY = 0;
    m_DirectionX = 1;
    m_FireTimer = 0;
    m_HurtTimer = 100;
    m_Health = 3;
    m_BlowingOrb = nullptr;


}

bool Player::hitTest(CollideActor& other)
{
    bool returnValue = false;
    if (CheckCollisionPointRec(other.getPosition(), getActorRectangle()) && m_HurtTimer < 0)
    {
        m_HurtTimer = 200;
        m_Health -= 1;
        m_VelY = -12;
        m_Landed = false;
        m_DirectionX = other.getDirectionX();
        if (m_Health > 0) 
        {
            //Play sound
            Game::getInstance()->playSound(std::string("ouch"), 4);
        }
        else 
        {
            //Play sound
            Game::getInstance()->playSound(std::string("die"));
        }
        returnValue = true;
    }

    return returnValue;
}

void Player::setHealth(int health)
{
    m_Health = health;
}

void Player::setLives(int lives)
{
    m_Lives = lives;
}

void Player::setScore(int score)
{
    m_Score = score;
}
