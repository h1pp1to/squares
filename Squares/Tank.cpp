#include "Tank.h"

#include "SFML/Window.hpp"
#include "WindowCfg.h"

Tank::Tank(Tanky::Cfg cfg)
{
    Init(cfg);
}

void Tank::Init(Tanky::Cfg cfg)
{
    rect.setPosition(cfg.xPos,cfg.yPos);
    rect.setSize({static_cast<float>(cfg.width), static_cast<float>(cfg.height)});
    color = cfg.color;
    rect.setFillColor(color);
    minSpeed = cfg.minSpeed;
    maxSpeed = cfg.maxSpeed;
    maxHealth = cfg.health;
    currentHealth = cfg.health;
    velocity = cfg.minSpeed;
}

void Tank::Move(Tank::Direction dir)
{
    collisionInfo = CollisionInfo::none;

    auto nextPosX = rect.getPosition().x;
    const int tankWidth = int(rect.getSize().x);
    if( dir == Direction::right )
    {
        nextPosX += velocity;
        if ((nextPosX + tankWidth) >= Window::width)
        {
            collisionInfo = CollisionInfo::rightWall;
            nextPosX = int(Window::width - tankWidth);
        }
    }
    else if ( dir == Direction::left )
    {
        nextPosX -= velocity;
        if (nextPosX <= 0)
        {
            collisionInfo = CollisionInfo::leftWall;
            nextPosX = 0;
        }
    }

    rect.setPosition(nextPosX, rect.getPosition().y);
}

void Tank::Update()
{
    gun.Update();
}

void Tank::Draw(sf::RenderWindow &window)
{
    window.draw(rect);
    gun.Draw(window);
}

void Tank::Hitted()
{

//    --currentHealth;
//    if (currentHealth <= 0)
//    {
//        return; //DEAD
//    }

//    float currentHealthPercent = float(currentHealth) / float(maxHealth);
//    float lostHealthPercent = 1.0f - currentHealthPercent;

//    velocity = minSpeed + ((maxSpeed - minSpeed) * lostHealthPercent);
}

void Tank::Shoot(Gun::Direction dir)
{
    int xCenter = int(rect.getPosition().x + (rect.getSize().x / 2));
    int yCenter = int(rect.getPosition().y + (rect.getSize().y / 2));
    gun.shoot(xCenter, yCenter, dir, rect.getFillColor());
}

Tank::CollisionInfo Tank::GetCollisionInfo()
{
    return collisionInfo;
}

sf::RectangleShape &Tank::getRect()
{
    return rect;
}

