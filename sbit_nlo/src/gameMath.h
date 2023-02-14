#pragma once
#include <SFML/Graphics.hpp>

class GameMath
{
public:
	static float length(sf::Vector2f vec);
	static float dist(sf::Vector2f vec1, sf::Vector2f vec2);
	static sf::Vector2f norm(sf::Vector2f vec);
};