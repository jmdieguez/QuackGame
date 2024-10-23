#ifndef COMMON_DUCK_H
#define COMMON_DUCK_H

struct DuckStatus {
public:
    bool shooting = false;
    bool looking_right = true;
    bool looking_up = false;
    bool has_chestplate = false;
    bool has_helmet = false;
    bool is_alive = true;
};

enum class DuckAction : uint8_t {
    IDLE = 0,
    MOVING,
    FLAPPING,
    LAYING,
    JUMPING
};

#endif // COMMON_DUCK_H
