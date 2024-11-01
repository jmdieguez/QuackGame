#ifndef COMMON_DUCK_H
#define COMMON_DUCK_H

#include <iostream>

struct DuckStatus {
    bool shooting = false;
    bool jumping = false;
    bool grounded = true;
    bool looking_right = true;
    bool looking_up = false;
    bool has_chestplate = false;
    bool has_helmet = false;
    bool is_alive = true;
};

enum class DuckAction : uint16_t {
    IDLE = 0,
    MOVING,
    FLAPPING,
    LAYING,
    JUMPING
};

#endif // COMMON_DUCK_H
