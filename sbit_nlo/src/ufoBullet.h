#pragma once
#include "entity.h"
#include <iostream>

class UFOBullet : public Entity
{
	sf::RectangleShape shape;
	sf::Vector2f pos;
	sf::Vector2f dir;
	float speed;
	void checkBounds();
public:
	UFOBullet(sf::Vector2f pos, sf::Vector2f dir, float speed);
	UFOBullet() { };
	void draw() override;
	void update() override;
	bool inBounds(sf::Vector2f pos) override;
	sf::FloatRect getBounds() override;
	void destroy() override { }
};