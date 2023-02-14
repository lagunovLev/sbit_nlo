#include "entity.h"
#include "game.h"

void Entity::drawHp()
{
	sf::FloatRect bounds = getBounds();
	static float margin = 3;


	sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(bounds.width, 14));
	rect.setFillColor(sf::Color(50, 50, 50, 255));
	rect.setPosition(sf::Vector2f(bounds.left, bounds.top + bounds.height + 5));
	Game::win.draw(rect);
	
	sf::RectangleShape rect2;
	rect2.setFillColor(sf::Color(0, 255, 0, 255));
	rect2.setPosition(sf::Vector2f(bounds.left + margin, bounds.top + bounds.height + 5 + margin));
	rect2.setSize(sf::Vector2f((bounds.width - margin * 2) * (hp / maxhp), 14 - margin * 2));
	Game::win.draw(rect2);
}

void Entity::getDamage(float damage)
{
	hp -= damage;
	if (hp <= 0)
		isAlive = false;
}

void Entity::drawWhole()
{
	draw();
	if (hp != maxhp) drawHp();
}