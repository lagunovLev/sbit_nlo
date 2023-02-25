#include "player.h"
#include "game.h"
#include "resourceManager.h"
#include "scenes/mainGame.h"
#include "bullet.h"
#include "gameMath.h"

#define BULLET_SPEED 250
#define BULLET_SIZE 8
#define BULLET_COST 25

Player::Player(sf::Vector2f pos, float speed, float scale)
{
	hp = maxhp = 80;
	sprite.setTexture(ResourceManager::getTexture("resources\\little_cannon.png"));
	sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y);
	sprite.setPosition(pos);
	sprite.setScale(scale, scale);
	this->speed = speed;
	this->isDestuctable = true;
}

void Player::draw()
{
	Game::win.draw(sprite);
}

void Player::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		sprite.move(-speed * Game::elapsedSeconds, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		sprite.move(speed * Game::elapsedSeconds, 0);

	float minX = ((MainGame*)Game::top())->ground.getPosition().x + sprite.getGlobalBounds().width / 2;
	float maxX = ((MainGame*)Game::top())->worldLength + minX - sprite.getGlobalBounds().width;
	if (sprite.getPosition().x < minX)
		sprite.setPosition(minX, sprite.getPosition().y);
	if (sprite.getPosition().x > maxX)
		sprite.setPosition(maxX, sprite.getPosition().y);

	minX = ((MainGame*)Game::top())->ground.getPosition().x + ((MainGame*)Game::top())->camera.getSize().x / 2;
	maxX = ((MainGame*)Game::top())->ground.getPosition().x + ((MainGame*)Game::top())->worldLength - ((MainGame*)Game::top())->camera.getSize().x / 2;
	((MainGame*)Game::top())->camera.setCenter(std::max<float>(minX, std::min<float>(sprite.getPosition().x, maxX)), ((MainGame*)Game::top())->camera.getCenter().y);

	reload = std::min(reload + 15 * Game::elapsedSeconds, max_reload);
	((MainGame*)Game::top())->player_reload = reload / max_reload;

	time += Game::elapsedSeconds;
	if (time >= 5) hp = std::min(hp + 3 * Game::elapsedSeconds, maxhp);
}

void Player::getDamage(float damage) 
{
	Entity::getDamage(damage);
	time = 0;
}

void Player::handleEvents(sf::Event e, sf::View view)
{
	if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
	{
		float scaleX = Game::win.getSize().x / view.getSize().x;
		float scaleY = Game::win.getSize().y / view.getSize().y;
		sf::Vector2f mousePos = sf::Vector2f(e.mouseButton.x / scaleX, e.mouseButton.y / scaleY);

		float spawn_y_offset = sprite.getGlobalBounds().height;
		sf::Vector2f pos = sf::Vector2f(((MainGame*)Game::top())->camera.getSize().x / 2, 
			((MainGame*)Game::top())->camera.getSize().y / 2 - spawn_y_offset) +
			 (sprite.getPosition() - ((MainGame*)Game::top())->camera.getCenter()); 
		sf::Vector2f dir = GameMath::norm(mousePos - pos);
		dir.x *= BULLET_SPEED;
		dir.y *= BULLET_SPEED;
		if (dir.y < 0 && reload >= BULLET_COST)
		{
			((MainGame*)Game::top())->entities.push_back(new Bullet(sprite.getPosition() - sf::Vector2f(0, spawn_y_offset), dir, BULLET_SIZE));
			reload -= BULLET_COST;
			((MainGame*)Game::top())->player_reload = reload / max_reload;
		}
	}
}

bool Player::inBounds(sf::Vector2f pos)
{
	return sprite.getGlobalBounds().contains(pos);
}

sf::FloatRect Player::getBounds()
{
	return sprite.getGlobalBounds();
}