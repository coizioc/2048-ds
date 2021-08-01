#ifndef VEC2_HPP
#define VEC2_HPP

#include <math.h>
#include <nds.h>

#include "consts.hpp"

struct Vec2 {
    int x;
    int y;

    Vec2() {
        Vec2(0, 0);
    }

    Vec2(int x, int y) {
        this->x = x;
        this->y = y;
    }

    Quadrant::Value quadrant() {
        bool x_pos = x > 0;
        bool y_pos = y > 0;

        if (x_pos && y_pos) {
            return Quadrant::Q1;
        } else if(!x_pos && y_pos) {
            return Quadrant::Q2;
        } else if(!x_pos && !y_pos) {
            return Quadrant::Q3;
        } else {
            return Quadrant::Q4;
        }
    }

    int magnitude() {
        return sqrtf32(inttof32(x * x + y * y));
    }

    bool operator==(const Vec2& v) {
        return this->x == v.x && this->y == v.y;
    }

    bool operator!=(const Vec2& v) {
        return !operator==(v);
    }
};

Vec2 getVelocity(int direction);

#endif
