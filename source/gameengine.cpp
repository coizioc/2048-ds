#include "gameengine.hpp"
#include "sprite_utils.hpp"
#include "state.hpp"

// GRIT auto-generated files
#include "tile_nums.h"
#include "tile_title.h"

void GameEngine::init() {
    consoleDebugInit(DebugDevice_NOCASH);

    oamInit(&oamSub, SpriteMapping_1D_256, false);
    m_tile_title = oamAllocateGfx(&oamSub, SpriteSize_64x64, SpriteColorFormat_256Color);
    dmaCopy(tile_titleTiles, m_tile_title, tile_titleTilesLen);
    dmaCopy(tile_titlePal, SPRITE_PALETTE_SUB, tile_titlePalLen);

    glLoadTileSet(
        m_tile_num_images,
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
    if (!m_states.empty()) {
        m_states.top()->dispose(this);
        m_states.pop();
    }

    m_states.push(state);
    m_states.top()->init(this);
}

void GameEngine::pushState(State* state) {
    if (!m_states.empty()) {
        m_states.top()->pause(this);
    }

    m_states.push(state);
    m_states.top()->init(this);
}

void GameEngine::popState() {
    if (!m_states.empty()) {
        m_states.top()->dispose(this);
        m_states.pop();
    }

    if (!m_states.empty()) {
        m_states.top()->resume(this);
    }
}

void GameEngine::handleEvents() {
    m_input_handler.update();
    if (!m_states.empty()) {
        m_states.top()->handleEvents(this);
    }
}

void GameEngine::update() {
    if (!m_states.empty()) {
        m_states.top()->update(this);
    }
}

void GameEngine::render() {
    if (!m_states.empty()) {
        m_states.top()->render(this);
    }
}

InputHandler& GameEngine::input_handler() {
    return m_input_handler;
}
