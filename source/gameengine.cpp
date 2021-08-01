#include "../include/gameengine.hpp"
#include "../include/state.hpp"

void GameEngine::init() {
    consoleDebugInit(DebugDevice_NOCASH);

    int tileNumTextureID = 
    glLoadTileSet(tile_num_images,
                    32,
                    32,
                    256,
                    128,
                    GL_RGB,
                    TEXTURE_SIZE_256,
                    TEXTURE_SIZE_128,
                    GL_TEXTURE_WRAP_S|GL_TEXTURE_WRAP_T|TEXGEN_OFF,
                    0,		// Just use 0 if palette is not in use
                    0,		// Just use 0 if palette is not in use
                    (u8*)tile_numsBitmap
                    );
}

void GameEngine::changeState(State* state) {
    if (!states.empty()) {
        states.top()->dispose(this);
        states.pop();
    }

    states.push(state);
    states.top()->init(this);
}

void GameEngine::pushState(State* state) {
    if (!states.empty()) {
        states.top()->pause(this);
    }

    states.push(state);
    states.top()->init(this);
}

void GameEngine::popState() {
    if (!states.empty()) {
        states.top()->dispose(this);
        states.pop();
    }

    if (!states.empty()) {
        states.top()->resume(this);
    }
}

void GameEngine::handleEvents() {
    input_handler.update();
    if (!states.empty()) {
        states.top()->handleEvents(this);
    }
}

void GameEngine::update() {
    if (!states.empty()) {
        states.top()->update(this);
    }
}

void GameEngine::render() {
    if (!states.empty()) {
        states.top()->render(this);
    }
}

InputHandler& GameEngine::inputHandler() {
    return input_handler;
}
