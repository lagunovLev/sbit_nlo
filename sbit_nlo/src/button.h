#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "resourceManager.h"

enum bState
{
    Usual,
    Pressed,
    Hovered
};

class Button
{
public:
    sf::Text sfText;
    bState state;
    std::function<void()> callback;
    sf::Sprite sprite;
    Button(std::string text, std::function<void()> callback, sf::Vector2f pos, int characterSize = 17, float scale = 2.0f, std::string path = "resources\\button.png");
    Button() { }
    bool handleEvent(sf::Event e, sf::View view);
    void draw();
    void updatePos(sf::Vector2f pos);
};
