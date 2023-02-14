#pragma once
class Game;

class State {
public:
    State* previous;
    bool run;
    virtual void start() = 0;
    virtual void input() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void destroy() = 0;
};

