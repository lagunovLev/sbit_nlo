#pragma once
#include <stack>
#include <SFML/Graphics.hpp>
#include "resourceManager.h"
class State;

class Game
{
    static void pop();
    static std::stack<State*> states;
    static sf::Clock clock;
    static void m_replace(State* state);
    static void m_push(State* state);

    static State* replace_pointer;
    static bool replace_or_push;
    static void check();
public:
    static float width;
    static float height;

    static float elapsedSeconds;
    static sf::RenderWindow win;

    static void replace(State* state);
    static void push(State* state);
    //static void insert(int place, State* state);
    static void run(State* startstate);
    static State* top();
};
