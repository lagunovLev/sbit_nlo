#pragma once
#include <SFML/Graphics.hpp>

class Background
{
	sf::Sprite sprite;
public:
	Background(sf::Texture& texture);
	Background() { };
	void draw(sf::Vector2f size);
};

