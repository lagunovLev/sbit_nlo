#include "gameMath.h"

float GameMath::length(sf::Vector2f vec) {
	return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}

float GameMath::dist(sf::Vector2f vec1, sf::Vector2f vec2) {
	return length(vec1 - vec2);
}

sf::Vector2f GameMath::norm(sf::Vector2f vec) {
	return vec / length(vec);
}