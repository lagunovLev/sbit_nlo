#include "Values.h"
#include "resourceManager.h"
#include "game.h"

#define MARGIN 5

Value::Value(std::string first, std::string second)
{
	f = sf::Sprite(ResourceManager::getTexture(first));
	s = sf::Sprite(ResourceManager::getTexture(second));
	f.setScale(2.0f, 2.0f);
	s.setScale(2.0f, 2.0f);
	t = sf::Text("", ResourceManager::getFont("resources\\DePixelBreit.otf"), 17);
	t.setFillColor(sf::Color(0, 0, 0, 255));
}

void Value::draw()
{
	Game::win.draw(f);
	Game::win.draw(s);
	Game::win.draw(t);
}

void Value::updateValue(std::string value)
{
	t.setString(value);
}

void Value::updatePosition(int x, int y)
{
	f.setPosition(x, y);
	s.setPosition(x, y);
	t.setPosition(x + f.getGlobalBounds().width + MARGIN, y + (f.getGlobalBounds().height - t.getGlobalBounds().height) / 2 - 2);
}

int Value::getWidth()
{
	return f.getGlobalBounds().width + MARGIN + t.getGlobalBounds().width;
}

int Value::getHeight()
{
	return f.getGlobalBounds().height;
}

int Value::getX()
{
	return f.getPosition().x;
}

int Value::getY()
{
	return f.getPosition().y;
}