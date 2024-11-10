#include "positiongun.h"

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

Position PositionGun::position_vertical(const Position &duck, const bool &looking_right)
{
    uint16_t pos_x = duck.x + (looking_right ? direc_vertical_right : direc_vertical_left);
    uint16_t pos_y = duck.y;
    return Position(pos_x, pos_y);
}

Position PositionGun::position_horizontal(const Position &duck, const bool &looking_right)
{
    uint16_t pos_x = duck.x + (looking_right ? direc_horizontal_right : direc_horizontal_left);
    uint16_t pos_y = duck.y + direc_horizontal_y;
    return Position(pos_x, pos_y);
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

PositionGun::PositionGun(const int &h_y, const int &h_r, const int &h_l, const int &v_r, const int &v_l) : direc_horizontal_y(h_y), direc_horizontal_right(h_r),
                                                                                                           direc_horizontal_left(h_l), direc_vertical_right(v_r),
                                                                                                           direc_vertical_left(v_l)
{
}

Position PositionGun::get_position(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up)
{
    (void)height_duck;
    return looking_up ? position_vertical(duck, looking_right) : position_horizontal(duck, looking_right);
};

PositionGun::~PositionGun()
{
}
