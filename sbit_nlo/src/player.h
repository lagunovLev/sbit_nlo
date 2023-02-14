#pragma once
#include "entity.h"

class Player : public Entity
{
protected:
	double reload = 100;
	double max_reload = 100;
public:
	sf::Sprite sprite;
	float time = 0;
	float speed;
	Player(sf::Vector2f pos, float speed, float scale = 1.0f);
	Player() { };
	void draw() override;
	void update() override;
	void handleEvents(sf::Event e);
	bool inBounds(sf::Vector2f pos) override;
	sf::FloatRect getBounds() override;
	void destroy() override { }
	void getDamage(float damage) override;
};