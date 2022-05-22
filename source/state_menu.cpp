#ifndef ARM9
#define ARM9
#endif
#include <nds.h>
#include "../lib/gl2d.h"

#include "animation.hpp"
#include "consts.hpp"
#include "sprite_utils.hpp"
#include "state_game.hpp"
#include "state_menu.hpp"
#include "vec2.hpp"

MenuState MenuState::s_state;

void MenuState::init(GameEngine* game) {
    const int y_offset = 150;
    const int x = 256 / 2 - 64 / 2;
    const int title_y = 192 / 2 - 64 / 2 - y_offset;
    const int play_y = 192 / 2 - 64 / 2 + y_offset;

    std::vector<int> ease_out_frame_values = Animations::ease_out(30, y_offset);
    for (std::vector<int>::iterator it = ease_out_frame_values.begin(); it != ease_out_frame_values.end(); it++) {
        int frame_value = *it;

        oamSet(&oamSub, 0, x, title_y + frame_value, 0, 0, SpriteSize_64x64, SpriteColorFormat_256Color, game->m_tile_title, 0, false, false, false, false, false);

        glBegin2D();
        glBoxFilled(0, 0, 255, 191, COLOR_BG);
        glEnd2D();
        glFlush(0);

        swiWaitForVBlank();
        oamUpdate(&oamSub);
    }

    ease_out_frame_values = Animations::ease_out(44, y_offset);
    for (std::vector<int>::iterator it = ease_out_frame_values.begin(); it != ease_out_frame_values.end(); it++) {
        int frame_value = *it;
        
        glBegin2D();
        
        glBoxFilled(0, 0, 255, 191, COLOR_BG);

        SpriteUtils::drawTwoByTwoTileSprite(game->m_tile_num_images + TILE_PLAY_BUTTON_IDX, x, play_y - frame_value, 32);

        glEnd2D();
        glFlush(0);

        swiWaitForVBlank();
    }
}

void MenuState::dispose(GameEngine* game) {

}

void MenuState::pause(GameEngine* game) {

}

void MenuState::resume(GameEngine* game) {

}

void MenuState::handleEvents(GameEngine* game) {
    int keys_pressed = keysDown();
    if (keys_pressed & KEY_TOUCH) {
        Vec2 touch_down = game->input_handler().touch_down();
        if (touch_down.x >= 256 / 2 - 32 && touch_down.x <= 256 / 2 + 32 && touch_down.y >= 192 / 2 - 32 && touch_down.y <= 192 / 2 + 32) {
            game->pushState(GameState::instance());
        }
    }
}

void MenuState::update(GameEngine* game) {
    
}

void MenuState::render(GameEngine* game) {
    
}
