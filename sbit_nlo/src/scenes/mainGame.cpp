#include "mainGame.h"
#include "../game.h"
#include "../resourceManager.h"
#include "lobby.h"
#include "../airship.h"
#include "pause.h"
#include "lose.h"

void MainGame::start()
{
    ground = Ground(ResourceManager::getTexture("resources\\grasstopwithoutair.png"), ResourceManager::getTexture("resources\\dirtfull.png"),
        sf::Vector2f(0.0f, 0.0f), 1.0f, 4.0f, worldLength);
    updateViews();
    sky = Background(ResourceManager::getTexture("resources\\sky.png"));
    pause = Button("pause", [&]() { bPausePressed = true; }, sf::Vector2f(85.0f, 40.0f), 17, 2, "resources\\button1.png");
    player = new Player(sf::Vector2f(worldLength / 2, 0), 100, 2);
    entities.push_back(player);
    spawner = EntitySpawner(&entities, 0.2);
    updateViews();
}

void MainGame::destroy()
{
    for (auto it = entities.begin(); it != entities.end(); it++)
        delete (*it);
    entities.clear();
}

void MainGame::display_values()
{
    static const int margin = 5;

    Value val = Value("resources\\little_airship.png", "resources\\cross.png");
    val.updateValue(std::to_string(airship_killed));

    Value val2 = Value("resources\\little_ufo.png", "resources\\cross.png");
    val2.updateValue(std::to_string(ufo_killed));

    int maxWidth = std::max(val.getWidth(), val2.getWidth());
    val2.updatePosition(view.getSize().x - maxWidth - margin, margin * 2 + val.getY() + val.getHeight());
    val.updatePosition(view.getSize().x - maxWidth - margin, margin);
    val2.draw();
    val.draw();

    int otstup = maxWidth + margin * 5;

    Value val3 = Value("resources\\little_airship.png", "resources\\little_airship.png");
    val3.updateValue(std::to_string(airship_passed));

    Value val4 = Value("resources\\little_ufo.png", "resources\\little_ufo.png");
    val4.updateValue(std::to_string(ufo_passed));
    

    maxWidth = std::max(val3.getWidth(), val4.getWidth());
    val4.updatePosition(view.getSize().x - otstup - maxWidth, margin * 2 + val3.getY() + val3.getHeight());
    val3.updatePosition(view.getSize().x - otstup - maxWidth, margin);
    val4.draw();
    val3.draw();

    static const int margin2 = 3;
    static const int height = 28;
    int length = view.getSize().x - margin * 2 - val4.getX();
    int h = val4.getHeight() + val4.getY() + margin;
    int x = val4.getX() + margin;

    auto shape = sf::RectangleShape(sf::Vector2f(length, height));
    shape.setFillColor(sf::Color(50, 50, 50, 255));
    shape.setPosition(sf::Vector2f(x, h));
    Game::win.draw(shape);

    auto shape2 = sf::RectangleShape(sf::Vector2f((length - margin2 * 2) * player_reload, height - margin2 * 2));
    shape2.setFillColor(sf::Color(255, 200, 0, 255));
    shape2.setPosition(sf::Vector2f(x + margin2, h + margin2));
    Game::win.draw(shape2);
}

void MainGame::input()
{
    updateViews();
    sf::Event e;
    while (Game::win.pollEvent(e))
    {
        if (pause.handleEvent(e, view))
        {
            if (bPausePressed) 
            {
                Game::push(new Pause());
                bPausePressed = false;
            }
            continue;
        } 

        if (e.type == sf::Event::Closed)
            run = false;

        player->handleEvents(e, view);
    }
    if (exit)
        Game::replace(new Lobby());
}

void MainGame::updateViews()
{
    float scaleY = Game::height / Game::win.getSize().y;
    view.setSize(scaleY * Game::win.getSize().x, Game::height);
    view.setCenter(sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2));

    camera.setSize(scaleY * Game::win.getSize().x, Game::height);
    camera.setCenter(sf::Vector2f(camera.getCenter().x, -(int)(camera.getSize().y / 2 + 1) + ground.getY()));
}

void MainGame::update()
{
    if (!player->isAlive) Game::push(new Lose(airship_passed, airship_killed, ufo_killed, ufo_passed)); // TODO

    auto it = entities.begin();
    while (it != entities.end())
    {
        (*it)->update();

        if (!(*it)->isAlive)
        {
            (*it)->destroy();
            it = entities.erase(it);
        }
        else it++;
    }

    spawner.spawn();
}

void MainGame::render()
{
    // objects with screen position
    Game::win.setView(view);
    sky.draw(sf::Vector2f(view.getSize().x, view.getSize().y));

    // objects with world position
    Game::win.setView(camera);
    ground.draw();
    for (auto it = entities.begin(); it != entities.end(); it++) {
        if ((*it)->isAlive) (*it)->drawWhole();
    }

    // objects with screen position
    Game::win.setView(view);
    display_values();
    pause.draw();
}