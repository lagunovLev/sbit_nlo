#pragma once
#include <SFML/Graphics.hpp>

class Ground
{
    float dirtLayersCount;
    float texScale;
    sf::Sprite grass;
    sf::Sprite dirt;
    float dirtLayerY;
    float grassLayerY;
public:
	Ground(sf::Texture& top, sf::Texture& bottom, sf::Vector2f pos, int layers, float texScale, int length);
    Ground() { };
    void draw();
    float getY();
    float getX();
    sf::Vector2f getPosition();
    sf::Vector2f getSize();
};