#include "background.h"
#include "game.h"

Background::Background(sf::Texture& texture)
{
	sprite.setPosition(sf::Vector2f(0, 0));
	sprite.setTexture(texture);
}

void Background::update(sf::Vector2f winSize)
{
	float scaleX = winSize.x / sprite.getTexture()->getSize().x;
	float scaleY = winSize.y / sprite.getTexture()->getSize().y;
	if (scaleX > scaleY)
		sprite.setScale(sf::Vector2f(scaleX, scaleX));
	else 
		sprite.setScale(sf::Vector2f(scaleY, scaleY));
}

void Background::draw()
{
	Game::win.draw(sprite);
}