#include "pause.h"
#include <iostream>
#include "../game.h"
#include "../resourceManager.h"
#include <SFML/Graphics.hpp>
#include "mainGame.h"
#include "lobby.h"

bool Pause::bContinuePressed;
bool Pause::bExitPressed;

void Pause::bContinueCallback()
{
    Pause::bContinuePressed = true;
}

void Pause::bExitCallback()
{
    Pause::bExitPressed = true;
}

void Pause::start()
{
    view = Game::win.getView();

    bContinuePressed = false;
    bExitPressed = false;
    b_continue = Button("continue", bContinueCallback, sf::Vector2f(Game::win.getSize().x / 2, Game::win.getSize().y / 2 - 50));
    exit = Button("exit", bExitCallback, sf::Vector2f(Game::win.getSize().x / 2, Game::win.getSize().y / 2 + 50));
}

void Pause::destroy()
{

}

void Pause::input()
{
    sf::Event e;
    while (Game::win.pollEvent(e))
    {
        if (b_continue.handleEvent(e) && bContinuePressed)
        {
            run = false;
            bContinuePressed = false;
            continue;
        }

        if (exit.handleEvent(e) && bExitPressed)
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
    view.setSize({ static_cast<float>(Game::win.getSize().x), static_cast<float>(Game::win.getSize().y) });
    view.setCenter(sf::Vector2f(Game::win.getSize().x / 2, Game::win.getSize().y / 2));
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
    rect.setSize(sf::Vector2f(Game::win.getSize().x, Game::win.getSize().y));
    Game::win.draw(rect);

    b_continue.draw();
    exit.draw();
}