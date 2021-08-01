#include <stdio.h>

#include "../include/input_handler.hpp"

void InputHandler::update() {
    scanKeys();

    pressed_keys = keysDown();
    held_keys = keysHeld();
    released_keys = keysUp();
    touchRead(&_tp);

    if (KEY_TOUCH & pressed_keys) {
        stylus_up = false;
        touch_down = Vec2(_tp.px, _tp.py);

        fprintf(stderr, "touchdown point: %d %d\n", touch_down.x, touch_down.y);

        if (touch_up != DEFAULT_TOUCH_POSITION) {
            touch_up = DEFAULT_TOUCH_POSITION;
        }
    } else if(KEY_TOUCH & held_keys) {
        stylus_up = false;
        if (touch_down != DEFAULT_TOUCH_POSITION) {
            fprintf(stderr, "touchup point: %d %d\n", touch_up.x, touch_up.y);
            touch_up = Vec2(_tp.px, _tp.py);
        }
    } else if (KEY_TOUCH & released_keys) {
        stylus_up = true;
    }
}

bool InputHandler::isSwipe() {
    return touch_down != DEFAULT_TOUCH_POSITION && touch_up != DEFAULT_TOUCH_POSITION && stylus_up;
}

int InputHandler::getSwipe() {
    Vec2 touch_vector = Vec2(touch_up.x - touch_down.x, -(touch_up.y - touch_down.y));

    fprintf(stderr, "touch vector: %d %d\n", touch_vector.x, touch_vector.y);

    touch_down = DEFAULT_TOUCH_POSITION;
    touch_up = DEFAULT_TOUCH_POSITION;

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
