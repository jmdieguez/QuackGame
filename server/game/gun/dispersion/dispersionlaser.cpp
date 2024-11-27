#include "dispersionlaser.h"

#define DIRECTION_VALUE -3
#define DIRECTION_VALUE_NEGATIVE 3

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

DispersionLaser::DispersionLaser() : change_direction(false)
{
}

DispersionLaser::DispersionLaser(const bool &change_direction) : change_direction(change_direction)
{
}

int DispersionLaser::calculate_dispersion(const uint16_t &x)
{
    (void)x;
    return change_direction ? DIRECTION_VALUE_NEGATIVE : DIRECTION_VALUE;
}

DispersionLaser::~DispersionLaser()
{
}
