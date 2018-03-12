#pragma once

#include "Tank.h"
#include "SFML/Window.hpp"
#include "Timer.h"

class AITank
{
public:
    void Init(Tanky::Cfg cfg);
    void Update();
    void Draw(sf::RenderWindow& window);
    void Shoot();
    Tank& GetTank();
private:
    Timer timer;
    Tank tank;
    Tank::Direction dir = Tank::Direction::right;
};
