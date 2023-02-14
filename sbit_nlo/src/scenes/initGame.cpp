#include "initGame.h"
#include "../game.h"
#include "lobby.h"
#include <random>
#include <time.h>

void InitGame::start()
{
    srand(time(NULL));
    Game::win.create(sf::VideoMode(1400, 900), "Game");
    Game::win.setVerticalSyncEnabled(true);
    Game::push(new Lobby());
    run = false;
}

void InitGame::destroy()
{
    Game::win.close();
    ResourceManager::free();
}

void InitGame::input()
{

}

void InitGame::update()
{

}

void InitGame::render()
{
    
}