#pragma once
#include "entity.h"

class Airship : public Entity
{
protected:
	sf::Sprite sprite;
	bool passed = false;
public:
	float speed;
	Airship(sf::Vector2f pos, float speed, float scale = 1.0f);
	Airship() { };
	void draw() override;
	void update() override;
	bool inBounds(sf::Vector2f pos) override;
	sf::FloatRect getBounds() override;
	void destroy() override;
};