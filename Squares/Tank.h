#pragma once

#include "SFML/Graphics.hpp"
#include "Gun.h"
#include "LevelCounter.h"

namespace Tanky
{
struct Cfg
{
    int health = 5;
    int minSpeed = 4;
    int maxSpeed = 10;
    int width = 50;
    int height = 50;
    int xPos = 0;
    int yPos = 0;
    sf::Color color = sf::Color::Red;
    bool enableLeveling = false;
};

}

class Tank
{
public:
    enum class Direction { left, right };
    enum class CollisionInfo { leftWall , rightWall , none};

    Tank() = default;
    Tank(Tanky::Cfg cfg);

    void Init(Tanky::Cfg cfg);
    void Move(Direction dir);
    void Update();
    void Draw(sf::RenderWindow& window);
    void Hitted();
    void Shoot(Gun::Direction dir);
    CollisionInfo GetCollisionInfo();
    sf::RectangleShape& getRect();
private:
    Gun gun;
    CollisionInfo collisionInfo = CollisionInfo::none;
    sf::RectangleShape rect;
    sf::Color color;

    int minSpeed = 4;
    int maxSpeed = 10;
    int maxHealth = 5;

    int currentHealth = 5;
    int velocity = 0; // horizontal direction

    LevelCounter levelCounter;
};
