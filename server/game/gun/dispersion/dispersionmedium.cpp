#include "dispersionmedium.h"

#define DIRECTION_VALUE -2
#define DIRECTION_VALUE_NEGATIVE 2

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

DispersionMedium::DispersionMedium() : change_direction(false)
{
}

DispersionMedium::DispersionMedium(const bool &change_direction) : change_direction(change_direction)
{
}

int DispersionMedium::calculate_dispersion(const uint16_t &x)
{
    (void)x;
    return change_direction ? DIRECTION_VALUE_NEGATIVE : DIRECTION_VALUE;
}

DispersionMedium::~DispersionMedium()
{
}
