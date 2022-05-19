#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#ifndef ARM9
#define ARM9
#endif
#include <nds.h>

#include "consts.hpp"
#include "vec2.hpp"

class InputHandler {
public:
    static const int KEY_ANY_DIRECTION = (KEY_UP | KEY_DOWN | KEY_LEFT | KEY_RIGHT);
    void update();
    bool isSwipe();
    int getSwipe();

    InputHandler() {
        stylus_up = true;
    }

    Vec2 touch_down();
    
private:
    const Vec2 DEFAULT_TOUCH_POSITION = Vec2(-1, -1);
    int pressed_keys;
    int held_keys;
    int released_keys;
    bool stylus_up;
    touchPosition _tp;
    Vec2 m_touch_down;
    Vec2 touch_up;
};

#endif
