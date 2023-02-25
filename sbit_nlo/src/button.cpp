#include "button.h"
#include "resourceManager.h"
#include "game.h"
#include <iostream>

Button::Button(std::string text, std::function<void()> callback, sf::Vector2f pos, int characterSize, float scale, std::string path)
{
    state = Usual;
    this->callback = callback;
    sf::Texture& texture = ResourceManager::getTexture(path);
    //texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    sprite.setScale(scale, scale);

    sfText.setFont(ResourceManager::getFont("resources\\DePixelBreit.otf"));
    sfText.setString(text);
    sfText.setCharacterSize(characterSize);
    sfText.setFillColor(sf::Color::Black);
    updatePos(pos);
}

bool Button::handleEvent(sf::Event e, sf::View view)
{
    float scaleX = Game::win.getSize().x / view.getSize().x;
    float scaleY = Game::win.getSize().y / view.getSize().y;
    sf::Vector2f location;
    if (e.type == sf::Event::MouseMoved)
        location = sf::Vector2f(e.mouseMove.x / scaleX, e.mouseMove.y / scaleY);
    else
    {
        sf::Vector2i cursorPos = sf::Mouse::getPosition(Game::win);
        location = sf::Vector2f(cursorPos.x / scaleX, cursorPos.y / scaleY);
    }

    if (e.type == sf::Event::MouseMoved && state != Pressed)
    {
        if (sprite.getGlobalBounds().contains(location)) state = Hovered;
        else state = Usual;
        return true;
    }
    if (e.type == sf::Event::MouseButtonPressed && state == Hovered && e.mouseButton.button == sf::Mouse::Left)
    {
        state = Pressed;
        return true;
    }
    if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left && state == Pressed)
    {
        if (sprite.getGlobalBounds().contains(location))
        {
            callback();
            state = Hovered;
        }
        else state = Usual;
        return true;
    }
    return false;
}

void Button::updatePos(sf::Vector2f pos)
{
    sprite.setPosition(pos);
    sfText.setPosition(pos - sf::Vector2f(sfText.getLocalBounds().width / 2, sfText.getLocalBounds().height / 2));
}

void Button::draw()
{
    sf::Color color;
    if (state == Usual)
        color = sf::Color(180, 180, 180);
    else if (state == Hovered)
        color = sf::Color(215, 215, 215);
    else if (state == Pressed)
        color = sf::Color(255, 255, 255);

    sprite.setColor(color);
    Game::win.draw(sprite);
    Game::win.draw(sfText);
}