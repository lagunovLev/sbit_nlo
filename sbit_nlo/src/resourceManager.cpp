#include "resourceManager.h"
#include <SFML/Graphics.hpp>

std::map<std::string, sf::Texture> ResourceManager::textures;
std::map<std::string, sf::Font> ResourceManager::fonts;

sf::Texture& ResourceManager::getTexture(std::string path)
{
    if (textures.count(path))
        return textures[path];

    textures.insert(make_pair(path, sf::Texture()));
    textures[path].loadFromFile(path);
    return textures[path];
}

sf::Font& ResourceManager::getFont(std::string path)
{
    if (fonts.count(path))
        return fonts[path];

    fonts.insert(make_pair(path, sf::Font()));
    fonts[path].loadFromFile(path);
    return fonts[path];
}

void ResourceManager::free()
{

}
