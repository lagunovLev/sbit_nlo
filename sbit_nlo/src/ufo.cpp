#include "ufo.h"
#include "game.h"
#include "resourceManager.h"
#include "scenes/mainGame.h"
#include "bullet.h"
#include "gameMath.h"
#include "ufoBullet.h"

UFO::UFO(sf::Vector2f pos, float speed, float scale) 
{
	hp = maxhp = 40;
	sprite.setTexture(ResourceManager::getTexture("resources\\ufo.png"));
	sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y);
	sprite.setPosition(pos);
	sprite.setScale(scale, scale);
	this->speed = speed;
	this->isDestuctable = true;
	reload = (float)rand() / RAND_MAX;
}

void UFO::update()
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

	reload += Game::elapsedSeconds * ((float)rand() / RAND_MAX * 0.1 + 0.05); 
	reload = std::min(reload, 1.0f);
	if (reload >= 1.0f && abs(((MainGame*)Game::top())->player->getBounds().left - sprite.getPosition().x) <= 600)
	{
		reload -= 1.0f;
		sf::Vector2f pos1 = sprite.getPosition() + sf::Vector2f(-sprite.getGlobalBounds().width / 2, 0);
		sf::Vector2f pos2 = sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2, 0);
		sf::Vector2f dir1 = GameMath::norm(((MainGame*)Game::top())->player->sprite.getPosition() - pos1);
		sf::Vector2f dir2 = GameMath::norm(((MainGame*)Game::top())->player->sprite.getPosition() - pos2);
		((MainGame*)Game::top())->entities.push_back(new UFOBullet(pos1, dir1, 240));
		((MainGame*)Game::top())->entities.push_back(new UFOBullet(pos2, dir2, 240));
	}
}

void UFO::destroy()
{
	if (passed) ((MainGame*)Game::top())->ufo_passed++;
	else ((MainGame*)Game::top())->ufo_killed++;
}