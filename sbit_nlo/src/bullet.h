#pragma once
#include "entity.h"
#include <list>

class Bullet : public Entity
{
	float timer = 0.0f;
	bool alive = true;
	sf::Vector2f pos;
	sf::Vector2f dir;
	std::list<sf::RectangleShape> squares;
	float size;
	sf::RectangleShape createSquare();
	void checkBounds();
public:
	Bullet(sf::Vector2f pos, sf::Vector2f dir, float size);
	Bullet() { };
	void draw() override;
	void update() override;
	bool inBounds(sf::Vector2f pos) override;
	sf::FloatRect getBounds() override;
	void destroy() override { }
};