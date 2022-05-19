#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <stack>

#include "../lib/gl2d.h"

#include "input_handler.hpp"

class State;

class GameEngine {
    std::stack<State*> states;
    InputHandler input_handler;
public:
    void init();
    void changeState(State* game_state);
    void pushState(State* game_state);
    void popState();

    void handleEvents();
    void update();
    void render();

    InputHandler& inputHandler();

    glImage tile_num_images[32];
    u16* tile_title;
};

#endif
