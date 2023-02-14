#pragma once
#include "../state.h"
#include <SFML/Graphics.hpp>
#include "../button.h"

class Lose : public State
{
    sf::View view;
    Button exit;
    static bool bExitPressed;
    static void bExitCallback();

    int airship_passed;
    int airship_killed;
    int ufo_killed;
    int ufo_passed;
public:
    void drawValues();
    Lose(int airship_passed, int airship_killed, int ufo_killed, int ufo_passed);
    void start() override;
    void input() override;
    void update() override;
    void render() override;
    void destroy() override;
};

