#include "dispersiongrenade.h"

#define DIRECTION_VALUE -3
#define DIRECTION_VALUE_NEGATIVE 3

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

DispersionGrenade::DispersionGrenade()
{
}

int DispersionGrenade::calculate_dispersion(const uint16_t &x)
{
    return x / 2;
}

DispersionGrenade::~DispersionGrenade()
{
}
