#ifndef MOVE_BACK_H
#define MOVE_BACK_H

#include "../../../common/position.h"

class MoveBack
{
private:
public:
    MoveBack() {};
    Position move_back(const Position &duck_position, const bool &looking_right, const uint8_t move_back) const
    {
        uint16_t new_pos_x = duck_position.x;
        new_pos_x += looking_right ? -move_back : move_back;
        Position new_position(new_pos_x, duck_position.y);
        return new_position;
    }
    ~MoveBack() {};
};

#endif // MOVE_BACK_H