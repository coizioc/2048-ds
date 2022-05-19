#include "animation.hpp"

/// y=-\frac{n}{t^{2}}\left(x-t\right)^{2}+n
std::vector<int> Animations::ease_out(int frames, int max_value) {
    std::vector<int> frame_values = std::vector<int>();

    float a = (float) max_value / (float)(frames * frames);

    for (int i = 0; i < frames; i++) {
        
        float dt2 = (float) (i - frames) * (i - frames);

        int value = (int) (-a * dt2 + (float)max_value);

        fprintf(stderr, "[%3d] Frame value: %d\n", i, value);
        frame_values.push_back(value);
    }

    return frame_values;
}

std::vector<int> Animations::ease_in(int frames, int max_value) {
    std::vector<int> frame_values = std::vector<int>();

    float a = (float) max_value / (float)(frames * frames);

    for (int i = 0; i < frames; i++) {
        
        float dt2 = (float) (frames * frames);

        int value = (int) (a * dt2 + (float)max_value);

        fprintf(stderr, "[%3d] Frame value: %d\n", i, value);
        frame_values.push_back(value);
    }

    return frame_values;
}
