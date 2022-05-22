#include <stdio.h>

#include "../include/input_handler.hpp"

void InputHandler::update() {
    scanKeys();

    m_pressed_keys = keysDown();
    m_held_keys = keysHeld();
    m_released_keys = keysUp();
    touchRead(&m_tp);

    if (KEY_TOUCH & m_pressed_keys) {
        m_stylus_up = false;
        m_touch_down = Vec2(m_tp.px, m_tp.py);

        fprintf(stderr, "touchdown point: %d %d\n", m_touch_down.x, m_touch_down.y);

        if (m_touch_up != DEFAULT_TOUCH_POSITION) {
            m_touch_up = DEFAULT_TOUCH_POSITION;
        }
    } else if(KEY_TOUCH & m_held_keys) {
        m_stylus_up = false;
        if (m_touch_down != DEFAULT_TOUCH_POSITION) {
            fprintf(stderr, "touchup point: %d %d\n", m_touch_up.x, m_touch_up.y);
            m_touch_up = Vec2(m_tp.px, m_tp.py);
        }
    } else if (KEY_TOUCH & m_released_keys) {
        m_stylus_up = true;
    }
}

 Vec2 InputHandler::touch_down() const {
    return m_touch_down;
}

bool InputHandler::isSwipe() {
    return m_touch_down != DEFAULT_TOUCH_POSITION && m_touch_up != DEFAULT_TOUCH_POSITION && m_stylus_up;
}

int InputHandler::getSwipe() {
    Vec2 touch_vector = Vec2(m_touch_up.x - m_touch_down.x, -(m_touch_up.y - m_touch_down.y));

    fprintf(stderr, "touch vector: %d %d\n", touch_vector.x, touch_vector.y);

    m_touch_down = DEFAULT_TOUCH_POSITION;
    m_touch_up = DEFAULT_TOUCH_POSITION;

    fprintf(stderr, "magnitude: %.2f\n", f32tofloat(touch_vector.magnitude()));

    if (touch_vector.magnitude() > floattof32(20.0)) {
        // Rotate touch_vector by 45 degrees so that the direction boundaries align with the x-y axes.
        Vec2 touch_vector_rot_45 = Vec2(touch_vector.x - touch_vector.y, touch_vector.x + touch_vector.y);

        fprintf(stderr, "touch touch_vector_rot_45: %d %d\n", touch_vector_rot_45.x, touch_vector_rot_45.y);

        switch(touch_vector_rot_45.quadrant()) {
            case Quadrant::Q1:
                return KEY_RIGHT;
            case Quadrant::Q2:
                return KEY_UP;
            case Quadrant::Q3:
                return KEY_LEFT;
            case Quadrant::Q4:
                return KEY_DOWN;
        }
    }

    return 0;
}
