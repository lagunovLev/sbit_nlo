#include "pause.h"
#include <iostream>
#include "../game.h"
#include "../resourceManager.h"
#include <SFML/Graphics.hpp>
#include "mainGame.h"
#include "lobby.h"

void Pause::start()
{
    update();
    b_continue = Button("continue", [&]() { bContinuePressed = true; }, sf::Vector2f(Game::win.getSize().x / 2, Game::win.getSize().y / 2 - 50));
    exit = Button("exit", [&]() { bExitPressed = true; }, sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2 + 50));
}

void Pause::destroy()
{

}

void Pause::input()
{
    sf::Event e;
    while (Game::win.pollEvent(e))
    {
        if (b_continue.handleEvent(e, view) && bContinuePressed)
        {
            run = false;
            bContinuePressed = false;
            continue;
        }

        if (exit.handleEvent(e, view) && bExitPressed)
        {
            run = false;
            ((MainGame*)(previous))->exit = true;
            bExitPressed = false;
            continue;
        }

        if (e.type == sf::Event::Closed)
        {
            previous->run = false;
            run = false;
        }

        if (e.type == sf::Event::Resized)
        {
            b_continue.updatePos(sf::Vector2f(Game::win.getSize().x / 2, Game::win.getSize().y / 2 - 50));
            exit.updatePos(sf::Vector2f(Game::win.getSize().x / 2, Game::win.getSize().y / 2 + 50));
        }
    }
}

void Pause::update()
{
    float scaleY = Game::height / Game::win.getSize().y;
    view.setSize(scaleY * Game::win.getSize().x, Game::height);
    view.setCenter(sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2));
    Game::win.setView(view);
    ((MainGame*)previous)->updateViews();
}

void Pause::render()
{
    previous->render();
    Game::win.setView(view);
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color(0, 0, 0, 100));
    rect.setPosition(0, 0);
    rect.setSize(sf::Vector2f(view.getSize().x, view.getSize().y));
    Game::win.draw(rect);

    b_continue.draw();
    exit.draw();
}