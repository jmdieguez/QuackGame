#ifndef COMMON_POSITION_H
#define COMMON_POSITION_H

#include <cstdint>

#include "snapshots.h"

class Position {
private:
    uint16_t pos_x;
    uint16_t pos_y;
public:
    Position(const uint16_t &initial_x, const uint16_t &initial_y) : pos_x(initial_x), pos_y(initial_y) {}
    ~Position() {}

    void move_x(const int &x) {
        pos_x += x;
    }

    PositionSnapshot get_status() {
        return PositionSnapshot(pos_x, pos_y);
    }
};

#endif // COMMON_POSITION_H
