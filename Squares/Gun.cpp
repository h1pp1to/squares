#include "Gun.h"

#include "WindowCfg.h"


void Gun::shoot(int x, int y, Direction dir,  sf::Color gunColor)
{
    sf::RectangleShape rect;
    rect.setPosition(x,y);
    rect.setSize({7,14});
    rect.setFillColor(gunColor);
    direction = dir;

    Bullet bullet;
    bullet.bulletVelocity = 5;
    bullet.rect = rect;
    bullet.alive = true;

    bullets.push_back(bullet);
}

void Gun::Update()
{
    auto iter = remove_if(bullets.begin(), bullets.end(), [](const auto& bullet)
    {
       return bullet.alive == false;
    });
    bullets.erase(iter, bullets.end());

    for (auto& bullet : bullets)
    {
        auto yPos = bullet.rect.getPosition().y;
        if (direction == Direction::up)
        {
            yPos -= bullet.bulletVelocity;
            if (yPos <= 0)
            {
                bullet.alive = false;
            }
        }
        else if (direction == Direction::down)
        {
            yPos += bullet.bulletVelocity;
            if (yPos >= Window::height)
            {
                bullet.alive = false;
            }
        }
        int xPos = int(bullet.rect.getPosition().x);
        bullet.rect.setPosition(xPos, yPos);
    }
}

void Gun::Draw(sf::RenderWindow &window)
{
    for (auto& bullet : bullets)
    {
        window.draw(bullet.rect);
    }
}
