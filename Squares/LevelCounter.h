#pragma once
#include <map>
#include "SFML/Graphics.hpp"

class LevelCounter
{
public:
    LevelCounter();

    void Enable();
    void GainExp();
    int GetCurrentLevel() const;
    int GetCurrentExp() const;
    void Draw(sf::RenderWindow& window);
private:
    bool enabled = false;
    sf::RectangleShape box;

    int currentLevel = 1;
    static const int expirienceRate = 1;
    static const int maxLevel = 5;
    std::map<int, int> expirienceRequirements;
    std::map<int, int> expirienceGained;
};
