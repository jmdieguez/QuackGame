#ifndef POSITION_GUN_H
#define POSITION_GUN_H

#include "../../../common/position.h"

class PositionGun
{
private:
    Position position_vertical(const Position &duck, const bool &looking_right);
    Position position_horizontal(const Position &duck, const bool &looking_right);

    int direc_horizontal_y;
    int direc_horizontal_right;
    int direc_horizontal_left;
    int direc_vertical_right;
    int direc_vertical_left;

public:
    explicit PositionGun(const int &h_y, const int &h_r, const int &h_l, const int &v_r, const int &v_l);
    Position get_position(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up);
    ~PositionGun();
};

#endif // POSITION_GUN_H