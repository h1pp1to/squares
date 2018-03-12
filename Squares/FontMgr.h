#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class FontMgr
{
//////////////////Singleton//////////////////
private:
    FontMgr();
public:
    FontMgr(const FontMgr &) = delete;
    void operator=(const FontMgr&) = delete;
    static FontMgr& Get();
/////////////////////////////////////////////

public:
    void AddFonts(std::string name, std::string path);
    sf::Font& GetFont(std::string name = "default");
private:
    std::map<std::string, sf::Font> fonts;
};

