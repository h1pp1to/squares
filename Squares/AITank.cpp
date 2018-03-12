#include "AITank.h"

#include "SFML/Graphics.hpp"
#include "WindowCfg.h"

AITank::AITank(Tanky::Cfg tankCfg)
    : tank(tankCfg)
{
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


