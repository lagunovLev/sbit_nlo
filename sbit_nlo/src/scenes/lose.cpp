#include "lose.h"
#include <iostream>
#include "../game.h"
#include "../resourceManager.h"
#include <SFML/Graphics.hpp>
#include "mainGame.h"
#include "lobby.h"

Lose::Lose(int airship_passed, int airship_killed, int ufo_killed, int ufo_passed) : airship_passed(airship_passed),
    airship_killed(airship_killed), ufo_killed(ufo_killed), ufo_passed(ufo_passed) { }

void Lose::start()
{
    update();
    exit = Button("exit", [&]() { bExitPressed = true; }, sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2 + 50));
}

void Lose::destroy()
{

}

void Lose::input()
{
    sf::Event e;
    while (Game::win.pollEvent(e))
    {
        if (exit.handleEvent(e, view) && bExitPressed)
        {
            run = false;
            ((MainGame*)(previous))->exit = true;
            previous->run = true;
            bExitPressed = false;
            continue;
        }

        if (e.type == sf::Event::Closed)
        {
            previous->run = false;
            run = false;
            ((MainGame*)(previous))->player->isAlive = true;
            return;
        }

        if (e.type == sf::Event::Resized)
        {
            exit.updatePos(sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2 + 50));
        }
    }
}

void Lose::update()
{
    float scaleY = Game::height / Game::win.getSize().y;
    view.setSize(scaleY * Game::win.getSize().x, Game::height);
    view.setCenter(sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2));
    Game::win.setView(view);
    ((MainGame*)previous)->updateViews();
}

void Lose::drawValues()
{
    int centerX = view.getSize().x / 2;
    int centerY = view.getSize().y / 2 - 100;
    static int margin = 5;

    sf::Text text = sf::Text("Game over", ResourceManager::getFont("resources\\DePixelBreit.otf"), 40);
    text.setFillColor(sf::Color(0, 0, 0, 255));
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(centerX, centerY);
    Game::win.draw(text);
}

void Lose::render()
{
    previous->render();
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color(0, 0, 0, 100));
    rect.setPosition(0, 0);
    rect.setSize(sf::Vector2f(view.getSize().x, view.getSize().y));
    Game::win.draw(rect);

    drawValues();
    exit.draw();
}