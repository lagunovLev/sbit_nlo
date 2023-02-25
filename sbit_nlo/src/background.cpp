#include "background.h"
#include "game.h"

Background::Background(sf::Texture& texture)
{
	sprite.setPosition(sf::Vector2f(0, 0));
	sprite.setTexture(texture);
}

void Background::draw(sf::Vector2f size)
{
	float scaleX = size.x / sprite.getTexture()->getSize().x;
	float scaleY = size.y / sprite.getTexture()->getSize().y;
	if (scaleX > scaleY)
		sprite.setScale(sf::Vector2f(scaleX, scaleX));
	else
		sprite.setScale(sf::Vector2f(scaleY, scaleY));

	Game::win.draw(sprite);
}