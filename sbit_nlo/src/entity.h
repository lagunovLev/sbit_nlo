#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
	float hp;
	float maxhp;
	bool isAlive = true;
	bool isDestuctable;

	virtual void draw() = 0;
	virtual void update() = 0;
	virtual bool inBounds(sf::Vector2f pos) = 0;
	virtual sf::FloatRect getBounds() = 0;
	virtual void destroy() = 0;
	void drawHp();
	virtual void getDamage(float damage);
	void drawWhole();
};