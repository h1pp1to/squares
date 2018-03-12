#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


#include "WindowCfg.h"

#include "Tank.h"
#include "AITank.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(Window::width, Window::height), "SFML window");
    window.setFramerateLimit(60);

    Tanky::Cfg playerCfg;
    playerCfg.yPos = Window::height - playerCfg.height;
    playerCfg.minSpeed = 8;
    Tank playerTank(playerCfg);

    Tanky::Cfg enemy1cfg;
    enemy1cfg.color = sf::Color::Black;
    enemy1cfg.xPos = Window::width / 2;
    enemy1cfg.health = 10;
    enemy1cfg.minSpeed = 3;
    enemy1cfg.maxSpeed = 10;

    Tanky::Cfg enemy2cfg;
    enemy2cfg.color = sf::Color::Blue;
    enemy2cfg.xPos = Window::width / 2;
    enemy2cfg.health = 10;
    enemy2cfg.minSpeed = 5;
    enemy2cfg.maxSpeed = 10;

    std::vector<AITank> aiTanks;
    aiTanks.push_back(AITank(enemy1cfg));
    aiTanks.push_back(AITank(enemy2cfg));

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
                  for(auto& aiTank : aiTanks){ aiTank.Shoot(); }
               }
           }
       }
       //Update part
       playerTank.Update();
       for(auto& aiTank : aiTanks)
       {
           aiTank.Update();
       }

       if (LeftKeyDown)
       {
           playerTank.Move(Tank::Direction::left);
       }
       else if (RightKeyDown)
       {
           playerTank.Move(Tank::Direction::right);
       }
       for(auto& aiTank : aiTanks){ aiTank.Update(); }


       //Draw part
       window.clear(sf::Color::White);

       playerTank.Draw(window);
       for(auto& aiTank : aiTanks){ aiTank.Draw(window); }

       window.display();
    }

    return 0;
}
