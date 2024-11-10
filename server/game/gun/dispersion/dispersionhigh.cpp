#include "dispersionhigh.h"

#define DIRECTION_VALUE -3
#define DIRECTION_VALUE_NEGATIVE 3

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

DispersionHigh::DispersionHigh() : change_direction(false)
{
}

DispersionHigh::DispersionHigh(const bool &change_direction) : change_direction(change_direction)
{
}

int DispersionHigh::calculate_dispersion(const uint16_t &x)
{
    (void)x;
    return change_direction ? DIRECTION_VALUE_NEGATIVE : DIRECTION_VALUE;
}

DispersionHigh::~DispersionHigh()
{
}
