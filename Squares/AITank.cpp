#include "AITank.h"
#include "Timer.h"
#include "SFML/Graphics.hpp"
#include "WindowCfg.h"

void AITank::Init(Tanky::Cfg cfg)
{
    tank.Init(cfg);
    timer.EveryOnce(500, [this]()
    {
        Shoot();
    });
}

void AITank::Update()
{
    if( tank.GetCollisionInfo() == Tank::CollisionInfo::leftWall )
    {
        dir = Tank::Direction::right;
    }
    else if(tank.GetCollisionInfo() == Tank::CollisionInfo::rightWall )
    {
        dir = Tank::Direction::left;
    }

    tank.Move(dir);
    tank.Update();

    timer.Update(15);
}

void AITank::Draw(sf::RenderWindow &window)
{
    tank.Draw(window);
}

void AITank::Shoot()
{
    tank.Shoot(Gun::Direction::down);
}

Tank &AITank::GetTank()
{
    return tank;
}


