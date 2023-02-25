#include "lobby.h"
#include <iostream>
#include "../game.h"
#include "../resourceManager.h"
#include <SFML/Graphics.hpp>
#include "mainGame.h"

void Lobby::start()
{
    view = Game::win.getDefaultView();
    Game::win.setView(view);

    bPlayPressed = false;
    bExitPressed = false;
    play = Button("play", [&]() { bPlayPressed = true; }, sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2 - 50));
    exit = Button("exit", [&]() { bExitPressed = true; }, sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2 + 50));

    sky = Background(ResourceManager::getTexture("resources\\sky.png"));
}

void Lobby::destroy()
{
    
}

void Lobby::input()
{
    sf::Event e;
    while (Game::win.pollEvent(e))
    {
        if(play.handleEvent(e, view) && bPlayPressed)
        {
            Game::replace(new MainGame());
            bPlayPressed = false;
            continue;
        }

        if (exit.handleEvent(e, view) && bExitPressed)
        {
            run = false;
            bExitPressed = false;
            continue;
        }

        if (e.type == sf::Event::Closed)
            run = false;

        if (e.type == sf::Event::Resized)
        {
            
        }
    }
}

void Lobby::update()
{
    float scaleY = Game::height / Game::win.getSize().y;
    view.setSize(scaleY * Game::win.getSize().x, Game::height);

    view.setCenter(sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2));
    Game::win.setView(view);

    play.updatePos(sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2 - 50));
    exit.updatePos(sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2 + 50));
}

void Lobby::render()
{
    sky.draw(sf::Vector2f(view.getSize().x, view.getSize().y));
    play.draw();
    exit.draw();
}