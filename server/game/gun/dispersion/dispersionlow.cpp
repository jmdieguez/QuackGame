#include "dispersionlow.h"

#define DIRECTION_VALUE -1
#define DIRECTION_VALUE_NEGATIVE 1

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

DispersionLow::DispersionLow() : change_direction(false)
{
}

DispersionLow::DispersionLow(const bool &change_direction) : change_direction(change_direction)
{
}

int DispersionLow::calculate_dispersion(const uint16_t &x)
{
    (void)x;
    return change_direction ? DIRECTION_VALUE_NEGATIVE : DIRECTION_VALUE;
}

DispersionLow::~DispersionLow()
{
}
