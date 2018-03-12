#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <vector>

class Gun
{
public:
    struct Bullet
    {
        sf::RectangleShape rect;
        bool alive = false;
        int bulletVelocity;
    };

    enum class Direction { up , down };
    void Draw(sf::RenderWindow& window);
    void Update();

    void shoot(int x, int y, Direction dir, sf::Color gunColor);
private:
    std::vector<Bullet> bullets;
    Direction direction;
};
