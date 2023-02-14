#include "game.h"
#include "state.h"
#include "iostream"

std::stack<State*> Game::states;
sf::Clock Game::clock;
sf::RenderWindow Game::win;
float Game::elapsedSeconds;

State* Game::replace_pointer = nullptr;
bool Game::replace_or_push;

void Game::run(State* startstate)
{
    m_push(startstate);
    while (!states.empty())
    {
        elapsedSeconds = clock.restart().asSeconds();
        states.top()->input();
        check();
        states.top()->update();
        check();
        Game::win.clear();
        states.top()->render();
        Game::win.display();
        check();
        if (!states.top()->run)
            pop();
    }
}

void Game::check()
{
    if (replace_pointer != nullptr)
    {
        if (replace_or_push)
            m_replace(replace_pointer);
        else
            m_push(replace_pointer);
        replace_pointer = nullptr;
    }
}

void Game::pop()
{
    states.top()->destroy();
    delete states.top();
    states.pop();
}

void Game::replace(State* state)
{
    replace_pointer = state;
    replace_or_push = true;
}

void Game::push(State* state)
{
    replace_pointer = state;
    replace_or_push = false;
}

void Game::m_push(State* state)
{
    if (states.size() >= 1)
        state->previous = states.top();
    else
        state->previous = nullptr;
    states.push(state);
    state->run = true;
    state->start();
}

//void Game::insert(int place, State* state)
//{
//    auto it = states.end() - 1;
//    it -= place + 1;
//    states.insert(it, state);
//    (*it)->previous = *(it - 1);
//}

State* Game::top() {
    return states.top();
}

void Game::m_replace(State* state) {
    pop();
    m_push(state);
}