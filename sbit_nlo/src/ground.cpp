#include "ground.h"
#include "game.h"

Ground::Ground(sf::Texture& top, sf::Texture& bottom, sf::Vector2f pos, int layers, float texScale, int length)
{
	dirtLayersCount = layers;
	this->texScale = texScale;

    top.setRepeated(true);
    bottom.setRepeated(true);
    grass.setScale(sf::Vector2f(texScale, texScale));
    dirt.setScale(sf::Vector2f(texScale, texScale));
    dirtLayerY = bottom.getSize().y * dirtLayersCount * texScale;
    grassLayerY = top.getSize().y * texScale;
    grass.setTexture(top);
    dirt.setTexture(bottom);

    grass.setPosition(pos);
    grass.setTextureRect({ 0, 0, static_cast<int>(length / texScale), static_cast<int>(grassLayerY / texScale) });
    dirt.setPosition(pos + sf::Vector2f(0, grassLayerY));
    dirt.setTextureRect({ 0, 0, static_cast<int>(length / texScale), static_cast<int>(dirtLayerY / texScale) });
}

void Ground::draw()
{
    Game::win.draw(dirt);
    Game::win.draw(grass);
}

sf::Vector2f Ground::getPosition()
{
    return grass.getPosition();
}

sf::Vector2f Ground::getSize()
{
    return sf::Vector2f(getX(), getY());
}

float Ground::getY()
{
    return dirtLayerY + grassLayerY;
}

float Ground::getX()
{
    return grass.getGlobalBounds().width;
}