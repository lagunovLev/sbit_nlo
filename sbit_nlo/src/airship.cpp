#include "airship.h"
#include "game.h"
#include "resourceManager.h"
#include "scenes/mainGame.h"
#include "bullet.h"
#include "gameMath.h"

Airship::Airship(sf::Vector2f pos, float speed, float scale)
{
	hp = maxhp = 40;
	sprite.setTexture(ResourceManager::getTexture("resources\\airship.png"));
	sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y);
	sprite.setPosition(pos);
	sprite.setScale(scale, scale);
	this->speed = speed;
	this->isDestuctable = true;
}

void Airship::draw()
{
	Game::win.draw(sprite);
}

void Airship::update()
{
	sf::Vector2f pos = sprite.getPosition();
	pos += sf::Vector2f(speed * Game::elapsedSeconds, 0);
	sprite.setPosition(pos);

	float minX = ((MainGame*)Game::top())->ground.getPosition().x - sprite.getGlobalBounds().width / 2;
	float maxX = ((MainGame*)Game::top())->worldLength + minX + sprite.getGlobalBounds().width;
	if (sprite.getPosition().x < minX || sprite.getPosition().x > maxX)
	{ 
		isAlive = false; 
		passed = true;
	}
}

bool Airship::inBounds(sf::Vector2f pos)
{
	return sprite.getGlobalBounds().contains(pos);
}

sf::FloatRect Airship::getBounds()
{
	return sprite.getGlobalBounds();
}

void Airship::destroy()
{
	if (passed) ((MainGame*)Game::top())->airship_passed++;
	else ((MainGame*)Game::top())->airship_killed++;
}