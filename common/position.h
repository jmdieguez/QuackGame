#ifndef COMMON_POSITION_H
#define COMMON_POSITION_H

#include <cstdint>
#include "snapshots.h"

class Position
{
public:
    uint16_t pos_x;
    uint16_t pos_y;

    Position(const uint16_t &initial_x, const uint16_t &initial_y) : pos_x(initial_x), pos_y(initial_y) {}

    PositionSnapshot get_status()
    {
        return PositionSnapshot(pos_x, pos_y);
    }

    ~Position() {}
};

#endif // COMMON_POSITION_H
