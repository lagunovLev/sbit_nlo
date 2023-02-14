#pragma once
#include "../state.h"
#include <SFML/Graphics.hpp>
#include "../button.h"
#include "../background.h"

class Pause : public State
{
    sf::View view;
    Button b_continue;
    static bool bContinuePressed;
    static void bContinueCallback();
    Button exit;
    static bool bExitPressed;
    static void bExitCallback();
public:
    Pause() { }
    void start() override;
    void input() override;
    void update() override;
    void render() override;
    void destroy() override;
};

