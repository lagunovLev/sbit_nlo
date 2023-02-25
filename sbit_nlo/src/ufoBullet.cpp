#include "ufoBullet.h"
#include "scenes/mainGame.h"
#include "game.h"
#include <math.h>
#include <algorithm>
#include "gameMath.h"
#include "scenes/mainGame.h"

#define SIZE 5

void UFOBullet::checkBounds()
{
	if (pos.y >= ((MainGame*)Game::top())->ground.getPosition().y || pos.y < -4000)
	{
		isAlive = false;
	}
}

UFOBullet::UFOBullet(sf::Vector2f pos, sf::Vector2f dir, float speed) : speed(speed), pos(pos), dir(dir)
{
	hp = maxhp = 0;
	shape.setSize(sf::Vector2f(5, 20));
	shape.setFillColor(sf::Color(0, 200, 0, 255));
	shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
	shape.setPosition(pos);
	shape.setRotation(atan2(dir.y, dir.x) * (180.0 / 3.14) + 90);
	this->isDestuctable = false;
	this->isAlive = true;
}

void UFOBullet::draw()
{
	shape.setPosition(pos);
	Game::win.draw(shape);
}

void UFOBullet::update()
{
	pos += dir * speed * Game::elapsedSeconds;
	checkBounds(); 

	for (auto it = ((MainGame*)Game::top())->entities.begin(); it != ((MainGame*)Game::top())->entities.end(); it++)
	{
		if ((*it)->isDestuctable && (*it)->inBounds(pos))
		{
			(*it)->getDamage(20); // TODO spawn explosion
			isAlive = false;
		}
	}
}

bool UFOBullet::inBounds(sf::Vector2f pos)
{
	return getBounds().contains(pos);
}

sf::FloatRect UFOBullet::getBounds()
{
	return sf::FloatRect(pos.x - SIZE, pos.y - SIZE, SIZE * 2, SIZE * 2);
}