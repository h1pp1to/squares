#include "FontMgr.h"
#include <iostream>

FontMgr::FontMgr()
{
    AddFonts("default", "../fonts/OpenSans-Regular.ttf");
    AddFonts("tusju", "../fonts/FFF_Tusj.ttf");
}

void FontMgr::AddFonts(std::string name, std::string path)
{
    sf::Font font;
    if(false == font.loadFromFile(path))
    {
        std::cout << "Failed to load font path: " << path;
        std::terminate();
    }
    fonts[name] = std::move(font);
}

sf::Font &FontMgr::GetFont(std::string name)
{
    auto iter = fonts.find(name);
    if( iter != fonts.end())
    {
        return iter->second;
    }
    return fonts.at("default");
}

FontMgr &FontMgr::Get()
{
    static FontMgr fontMgr;
    return fontMgr;
}
