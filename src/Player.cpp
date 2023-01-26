#include "Player.h"
#include "ResourceManager.h"
#include "Game.h"

Player::Player(Vector2 pos, Texture2D* image) : GravityActor(pos, image)
{
    setImage(*ResourceManager::getSprite(std::string("still")));
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
    if (IsKeyDown(KEY_LEFT)) 
    {
        m_Dx = -1;
    }
    else if (IsKeyDown(KEY_RIGHT))
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

    if (IsKeyDown(KEY_UP) && m_VelY == 0 && m_Landed) 
    {
        m_VelY = -16;
        m_Landed = false;
        //Play sound
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
    //m_BlowingOrb = None;
}

bool Player::hitTest(CollideActor& other)
{
    bool returnValue = false;
    if (CheckCollisionPointRec(other.getPosition(), getImageRectangle()) && m_HurtTimer < 0)
    {
        m_HurtTimer = 200;
        m_Health -= 1;
        m_VelY = -12;
        m_Landed = false;
        m_DirectionX = other.getDirectionX();
        if (m_Health > 0) 
        {
            //Play sound
        }
        else 
        {
            //Play sound
        }
        returnValue = true;
    }

    return returnValue;
}
