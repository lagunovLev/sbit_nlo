#pragma once
#include <SFML/Graphics.hpp>

class Background
{
	sf::Sprite sprite;
public:
	Background(sf::Texture& texture);
	Background() { };
	void update(sf::Vector2f winSize);
	void draw();
};

