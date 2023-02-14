#include "lose.h"
#include <iostream>
#include "../game.h"
#include "../resourceManager.h"
#include <SFML/Graphics.hpp>
#include "mainGame.h"
#include "lobby.h"

bool Lose::bExitPressed;

void Lose::bExitCallback()
{
    Lose::bExitPressed = true;
}

Lose::Lose(int airship_passed, int airship_killed, int ufo_killed, int ufo_passed) : airship_passed(airship_passed),
    airship_killed(airship_killed), ufo_killed(ufo_killed), ufo_passed(ufo_passed) { }

void Lose::start()
{
    view = Game::win.getView();
    Game::win.setView(view);

    bExitPressed = false;
    exit = Button("exit", bExitCallback, sf::Vector2f(Game::win.getSize().x / 2, Game::win.getSize().y / 2 + 50));
}

void Lose::destroy()
{

}

void Lose::input()
{
    sf::Event e;
    while (Game::win.pollEvent(e))
    {
        if (exit.handleEvent(e) && bExitPressed)
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
            exit.updatePos(sf::Vector2f(Game::win.getSize().x / 2, Game::win.getSize().y / 2 + 50));
        }
    }
}

void Lose::update()
{
    view.setSize({ static_cast<float>(Game::win.getSize().x), static_cast<float>(Game::win.getSize().y) });
    view.setCenter(sf::Vector2f(Game::win.getSize().x / 2, Game::win.getSize().y / 2));
    Game::win.setView(view);
    ((MainGame*)previous)->updateViews();
}

void Lose::drawValues()
{
    int centerX = Game::win.getSize().x / 2;
    int centerY = Game::win.getSize().y / 2 - 100;
    static int margin = 5;
    
    //Value val = Value("resources\\little_airship.png", "resources\\cross.png");
    //val.updateValue(std::to_string(airship_killed));
    //val.updatePosition(centerX, centerY - val.getHeight() - margin);
    //val.draw();
    //
    //Value val2 = Value("resources\\little_ufo.png", "resources\\cross.png");
    //val2.updateValue(std::to_string(ufo_killed));
    //val2.updatePosition(centerX, centerY + val2.getHeight() + margin);
    //val2.draw();
    //
    //int otstup = std::max(val.getWidth(), val2.getWidth()) + margin * 5;
    //
    //Value val3 = Value("resources\\little_airship.png", "resources\\little_airship.png");
    //val3.updateValue(std::to_string(airship_passed));
    //val3.updatePosition(Game::win.getSize().x - otstup - val3.getWidth(), margin);
    //val3.draw();
    //
    //Value val4 = Value("resources\\little_ufo.png", "resources\\little_ufo.png");
    //val4.updateValue(std::to_string(ufo_passed));
    //val4.updatePosition(Game::win.getSize().x - otstup - val4.getWidth(), margin + val3.getY() + val3.getHeight());
    //val4.draw();

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
    rect.setSize(sf::Vector2f(Game::win.getSize().x, Game::win.getSize().y));
    Game::win.draw(rect);

    drawValues();
    exit.draw();
}