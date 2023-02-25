#include "bullet.h"
#include "scenes/mainGame.h"
#include "game.h"
#include <math.h>
#include <algorithm>
#include "gameMath.h"
#include "scenes/mainGame.h"

#define TIME 10
#define TAIL_LENGTH 7
#define GRAVITATION 32

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f dir, float size)
{
	hp = maxhp = 0;
	this->pos = pos;
	this->dir = dir;
	this->size = size;
	this->isDestuctable = false;
	squares.push_back(createSquare());
}

void Bullet::draw()
{
	for (auto it = squares.begin(); it != squares.end(); it++) {
		Game::win.draw(*it);
	}
	if (alive) Game::win.draw(createSquare()); // TODO
}

sf::RectangleShape Bullet::createSquare()
{
	sf::RectangleShape square;
	square.setOrigin(size / 2.0f, size / 2.0f);
	square.setFillColor(sf::Color(255, 100, 0, 255));
	square.setPosition(pos);
	square.setSize(sf::Vector2f(size, size));
	return square;
}

void Bullet::checkBounds()
{
	if (pos.y >= ((MainGame*)Game::top())->ground.getPosition().y)
		alive = false;
}

void Bullet::update()
{
	// TODO add gravitation, destroy bullets, spawn explosion
	if (alive)
	{
		pos += dir * Game::elapsedSeconds;
		dir.y += GRAVITATION * Game::elapsedSeconds;
	}
	timer += TIME * Game::elapsedSeconds;

	for (std::list<sf::RectangleShape>::iterator it = squares.begin(); it != squares.end(); it++)
	{
		sf::Color color = it->getFillColor();
		auto changed_color = color;

		changed_color.a = std::max<float>(color.a * 1.0, 0);
		changed_color.r = std::max<float>(color.r * 0.7 - 10, 0);
		changed_color.g = std::max<float>(color.b * 0.7 - 10, 0);

		color.a -= (color.a - changed_color.a) * Game::elapsedSeconds;
		color.r -= (color.r - changed_color.r) * Game::elapsedSeconds;
		color.g -= (color.g - changed_color.g) * Game::elapsedSeconds;

		it->setFillColor(color);
		it->setSize(it->getSize() - sf::Vector2f(7, 7) * Game::elapsedSeconds);
	}

	if (timer >= 1.0f)
	{
		if (alive)
			squares.push_back(createSquare());
		if (!alive || squares.size() >= TAIL_LENGTH)
			squares.erase(squares.begin());
		timer -= 1.0f;
	}
	checkBounds();

	if (alive)
	{
		for (auto it = ((MainGame*)Game::top())->entities.begin(); it != ((MainGame*)Game::top())->entities.end(); it++)
		{
			if ((*it)->isDestuctable && (*it)->inBounds(pos))
			{ 
				(*it)->getDamage(40); // TODO spawn explosion
				alive = false;
			}
		}
	}

	if (squares.empty())
		isAlive = false;
}

bool Bullet::inBounds(sf::Vector2f pos)
{
	float halfSize = size / 2.0f;
	return sf::FloatRect({ pos.x - halfSize, pos.y - halfSize, size, size }).contains(pos);
}

sf::FloatRect Bullet::getBounds()
{
	float halfSize = size / 2.0f;
	return sf::FloatRect({ pos.x - halfSize, pos.y - halfSize, size, size });
}