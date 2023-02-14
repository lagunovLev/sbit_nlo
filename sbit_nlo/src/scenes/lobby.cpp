#include "lobby.h"
#include <iostream>
#include "../game.h"
#include "../resourceManager.h"
#include <SFML/Graphics.hpp>
#include "mainGame.h"

bool Lobby::bPlayPressed;
bool Lobby::bExitPressed;

void Lobby::bPlayCallback()
{
    Lobby::bPlayPressed = true;
}

void Lobby::bExitCallback()
{
    Lobby::bExitPressed = true;
}

void Lobby::start()
{
    view = Game::win.getDefaultView();
    Game::win.setView(view);

    bPlayPressed = false;
    bExitPressed = false;
    play = Button("play", bPlayCallback, sf::Vector2f(Game::win.getSize().x / 2, Game::win.getSize().y / 2 - 50));
    exit = Button("exit", bExitCallback, sf::Vector2f(Game::win.getSize().x / 2, Game::win.getSize().y / 2 + 50));

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
        if(play.handleEvent(e) && bPlayPressed)
        {
            Game::replace(new MainGame());
            bPlayPressed = false;
            continue;
        }

        if (exit.handleEvent(e) && bExitPressed)
        {
            run = false;
            bExitPressed = false;
            continue;
        }

        if (e.type == sf::Event::Closed)
            run = false;

        if (e.type == sf::Event::Resized)
        {
            play.updatePos(sf::Vector2f(Game::win.getSize().x / 2, Game::win.getSize().y / 2 - 50));
            exit.updatePos(sf::Vector2f(Game::win.getSize().x / 2, Game::win.getSize().y / 2 + 50));
            sky.update(sf::Vector2f(e.size.width, e.size.height));
        }
    }
}

void Lobby::update()
{
    view.setSize({ static_cast<float>(Game::win.getSize().x), static_cast<float>(Game::win.getSize().y) });
    view.setCenter(sf::Vector2f(Game::win.getSize().x / 2, Game::win.getSize().y / 2));
    Game::win.setView(view);
}

void Lobby::render()
{
    sky.draw();
    play.draw();
    exit.draw();
}