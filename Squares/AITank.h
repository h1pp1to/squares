#pragma once

#include "Tank.h"
#include "SFML/Window.hpp"

class AITank
{
public:
    AITank(Tanky::Cfg tank);

    void Update();
    void Draw(sf::RenderWindow& window);
    void Shoot();
    Tank& GetTank();
private:
    Tank tank;
    Tank::Direction dir = Tank::Direction::right;
};
