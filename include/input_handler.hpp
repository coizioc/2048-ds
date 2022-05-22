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
        m_stylus_up = true;
    }

    Vec2 touch_down() const;
    
private:
    const Vec2 DEFAULT_TOUCH_POSITION = Vec2(-1, -1);
    int m_pressed_keys;
    int m_held_keys;
    int m_released_keys;
    bool m_stylus_up;
    touchPosition m_tp;
    Vec2 m_touch_down;
    Vec2 m_touch_up;
};

#endif
