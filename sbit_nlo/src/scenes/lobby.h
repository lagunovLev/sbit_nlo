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
    static bool bPlayPressed;
    static void bPlayCallback();
    Button exit;
    static bool bExitPressed;
    static void bExitCallback();
public:
    Lobby() { }
    void start() override;
    void input() override;
    void update() override;
    void render() override;
    void destroy() override;
};

