#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <cstdio>
#include <vector>

namespace Animations {

std::vector<int> ease_out(int frames, int max_value);
std::vector<int> ease_in(int frames, int max_value);

}

#endif
