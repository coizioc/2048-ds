#ifndef STATE_HPP
#define STATE_HPP

#include "gameengine.hpp"

class State {
public:
    virtual void init(GameEngine* game) = 0;
    virtual void dispose(GameEngine* game) = 0;

    virtual void pause(GameEngine* game) = 0;
    virtual void resume(GameEngine* game) = 0;

    virtual void handleEvents(GameEngine* game) = 0;
    virtual void update(GameEngine* game) = 0;
    virtual void render(GameEngine* game) = 0;

    void changeState(GameEngine* game, State* state) {
        game->changeState(state);
    }

protected:
    State() {}
};

#endif
