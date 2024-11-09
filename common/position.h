#ifndef COMMON_POSITION_H
#define COMMON_POSITION_H

#include <cstdint>

class Position
{
public:
    uint16_t x;
    uint16_t y;

    Position(const uint16_t &initial_x, const uint16_t &initial_y) : x(initial_x), y(initial_y) {}

    ~Position() {}
};

#endif // COMMON_POSITION_H
