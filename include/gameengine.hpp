#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <stack>

#include "../lib/gl2d.h"

#include "input_handler.hpp"

class State;

class GameEngine {
    std::stack<State*> m_states;
    InputHandler m_input_handler;
public:
    void init();
    void changeState(State* game_state);
    void pushState(State* game_state);
    void popState();

    void handleEvents();
    void update();
    void render();

    InputHandler& input_handler();

    glImage m_tile_num_images[32];
    u16* m_tile_title;
};

#endif
