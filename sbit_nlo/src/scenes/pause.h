#pragma once
#include "../state.h"
#include <SFML/Graphics.hpp>
#include "../button.h"
#include "../background.h"

class Pause : public State
{
    sf::View view;
    Button b_continue;
    bool bContinuePressed = false;
    Button exit;
    bool bExitPressed = false;
public:
    Pause() { }
    void start() override;
    void input() override;
    void update() override;
    void render() override;
    void destroy() override;
};

