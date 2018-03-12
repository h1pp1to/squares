#include "LevelCounter.h"
#include "FontMgr.h"

LevelCounter::LevelCounter()
{
    int expRate = expirienceRate;
    for(int i = 1; i <= maxLevel; i++)
    {
        expirienceRequirements[i] = expRate;
        expirienceGained[i] = 0;
        expRate *= 2;
    }

    box.setSize({800, 40});
    box.setPosition(230, 700);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2);
}

void LevelCounter::Enable()
{
    enabled = true;
}

void LevelCounter::GainExp()
{
    if( false == enabled ){ return; }

    if( currentLevel == maxLevel )
    {
        return;
    }

    auto exp = expirienceGained.at(currentLevel)++;
    if( exp >= expirienceRequirements.at(currentLevel) )
    {
        currentLevel++;
    }
}

int LevelCounter::GetCurrentLevel() const
{
    return currentLevel;
}

int LevelCounter::GetCurrentExp() const
{
    return expirienceGained.at(currentLevel);
}

void LevelCounter::Draw(sf::RenderWindow &window)
{
    if( false == enabled ){ return; }

    auto& font = FontMgr::Get().GetFont();

    //1. Draw current level
    auto pos = box.getPosition();
    sf::Text txtLvl;
    txtLvl.setPosition(pos.x - 115, pos.y);
    txtLvl.setFont(font);
    txtLvl.setFillColor(sf::Color::Black);
    txtLvl.setString("Level: " + std::to_string(currentLevel));
    window.draw(txtLvl);

    //2. Draw exp bar
    if( currentLevel == maxLevel )
    {
        box.setFillColor(sf::Color::Cyan);
        window.draw(box);
    }
    else
    {
        int currentExp = expirienceGained.at(currentLevel);
        int requiredExp = expirienceRequirements.at(currentLevel);
        float percentageToLvlUp = float(currentExp) / float(requiredExp);

        int boxWidth = int(box.getSize().x);
        float expBarLength = float(boxWidth) * percentageToLvlUp;

        auto expBarRect = box;
        expBarRect.setSize({expBarLength, box.getSize().y});
        expBarRect.setFillColor(sf::Color::Cyan);

        window.draw(box);
        window.draw(expBarRect);

        sf::Text txtExpGained;
        std::string expGainedStr = std::to_string(currentExp) + " / " + std::to_string(requiredExp);
        txtExpGained.setString(expGainedStr);
        int centerTxtPos = pos.x + ((boxWidth - expGainedStr.size()) / 2);
        txtExpGained.setPosition(centerTxtPos, pos.y);
        txtExpGained.setFont(font);
        txtExpGained.setFillColor(sf::Color::Black);
        window.draw(txtExpGained);
    }
}
