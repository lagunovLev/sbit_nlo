#pragma once
#include "../state.h"
#include <SFML/Graphics.hpp>

class InitGame : public State
{
public:
    InitGame() { }
    void start() override;
    void input() override;
    void update() override;
    void render() override;
    void destroy() override;
};

