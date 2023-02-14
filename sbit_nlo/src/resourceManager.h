#pragma once
#include <map>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

class ResourceManager
{
    static std::map<std::string, sf::Texture> textures;
    static std::map<std::string, sf::Font> fonts;
public:
    static sf::Texture& getTexture(std::string path);
    static sf::Font& getFont(std::string path);
    static void free();
};
