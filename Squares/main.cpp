#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "WindowCfg.h"
#include "Timer.h"
#include "Tank.h"
#include "AITank.h"

Tanky::Cfg GetPlayerCfg();
Tanky::Cfg GetRandomCfg();

static const int AI_TANK_COUNT = 2;
int main()
{
    sf::RenderWindow window(sf::VideoMode(Window::width, Window::height), "SFML window");
    window.setFramerateLimit(60);

    Tank playerTank( GetPlayerCfg() );

    std::vector<AITank> aiTanks(AI_TANK_COUNT);
    for(auto& aiTank : aiTanks )
    {
        auto cfg = GetRandomCfg();
        aiTank.Init(cfg);
    }

    bool LeftKeyDown = false;
    bool RightKeyDown = false;
    while (window.isOpen())
    {
       sf::Event event;
       while (window.pollEvent(event))
       {
           if (event.type == sf::Event::Closed)
               window.close();

           if (event.type == sf::Event::KeyPressed)
           {
               if (event.key.code == sf::Keyboard::A)
               {
                    LeftKeyDown = true;
                    RightKeyDown = false;
               }
               if (event.key.code == sf::Keyboard::D)
               {
                   RightKeyDown = true;
                   LeftKeyDown = false;
               }
           }
           if (event.type == sf::Event::MouseButtonPressed)
           {
               if (event.mouseButton.button == sf::Mouse::Left)
               {
                  playerTank.Shoot(Gun::Direction::up);
//                  for(auto& aiTank : aiTanks){ aiTank.Shoot(); }
               }
           }
       }
       //Update part
       if (LeftKeyDown)
       {
           playerTank.Move(Tank::Direction::left);
       }
       else if (RightKeyDown)
       {
           playerTank.Move(Tank::Direction::right);
       }

       playerTank.Update();
       for(auto& aiTank : aiTanks)
       {
           aiTank.Update();
       }

       //Draw part
       window.clear(sf::Color::White);

       playerTank.Draw(window);
       for(auto& aiTank : aiTanks)
       {
           aiTank.Draw(window);
       }

       window.display();
    }

    return 0;
}


Tanky::Cfg GetPlayerCfg()
{
    Tanky::Cfg playerCfg;
    playerCfg.yPos = Window::height - playerCfg.height;
    playerCfg.minSpeed = 8;
    playerCfg.enableLeveling = true;
    return playerCfg;
}

Tanky::Cfg GetRandomCfg()
{
    static std::vector<sf::Color> colors =
    {
        sf::Color::Red,
        sf::Color::Black,
        sf::Color::Yellow,
        sf::Color::Green,
        sf::Color::Cyan
    };
    static size_t next_color_id = 0;
    if( next_color_id == colors.size() - 1)
    {
        next_color_id = 0;
    }

    Tanky::Cfg enemy1cfg;
    enemy1cfg.color = colors.at(next_color_id++);
    enemy1cfg.xPos = Window::width / 2;
    enemy1cfg.health = (rand() % 10 + 1);
    enemy1cfg.minSpeed = (rand() % 10 + 1);
    enemy1cfg.maxSpeed = (rand() % 15 + 5);
    return enemy1cfg;
}
