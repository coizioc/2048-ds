#include "../include/vec2.hpp"

Vec2 getVelocity(int keys_pressed) {
    if (KEY_UP & keys_pressed) {
        return Vec2(0, -1);
    } else if (KEY_DOWN & keys_pressed) {
        return Vec2(0, 1);
    } else if(KEY_LEFT & keys_pressed) {
        return Vec2(-1, 0);
    } else if (KEY_RIGHT & keys_pressed) {
        return Vec2(1, 0);
    } else {
        return Vec2(0, 0);
    }
}
