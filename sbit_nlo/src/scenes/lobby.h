#pragma once
#include "../state.h"
#include <SFML/Graphics.hpp>
#include "../button.h"
#include "../background.h"

class Lobby : public State
{
    sf::View view;
    Background sky;
    Button play;
    bool bPlayPressed = false;
    Button exit;
    bool bExitPressed = false;
public:
    Lobby() { }
    void start() override;
    void input() override;
    void update() override;
    void render() override;
    void destroy() override;
};

