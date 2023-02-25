#pragma once
#include "../state.h"
#include <SFML/Graphics.hpp>
#include "../button.h"
#include "../background.h"
#include "../ground.h"
#include "../player.h"
#include "../bullet.h"
#include "../entitySpawner.h"
#include "../Values.h"

class MainGame : public State
{
    Background sky;
    EntitySpawner spawner;

    Button pause;
    bool bPausePressed = false;
    void display_values();
public:
    unsigned int ufo_killed = 0;
    unsigned int airship_killed = 0;
    unsigned int ufo_passed = 0;
    unsigned int airship_passed = 0;
    double player_reload = 0;

    bool exit = false;
    Ground ground;
    float worldLength = 2000;
    sf::View camera;
    sf::View view;
    Player* player;
    std::list<Entity*> entities;

    void updateViews();
    MainGame() { }
    void start() override;
    void input() override;
    void update() override;
    void render() override;
    void destroy() override;
};

