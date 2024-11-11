#ifndef COMMON_DUCK_H
#define COMMON_DUCK_H

#include <iostream>
#include <cstdint>

struct DuckStatus
{
    bool mooving = false;
    bool shooting = false;
    bool jumping = false;
    bool start_jumping = false;
    bool falling = false;
    bool flapping = false;
    bool bent_down = false;
    bool grounded = false;
    bool looking_up = false;
    bool looking_right = false;
    bool has_helmet = false;
    bool has_chestplate = false;
    bool is_alive = true;
};

#endif // COMMON_DUCK_H
