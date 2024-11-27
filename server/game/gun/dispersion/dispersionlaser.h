#ifndef DISPERSION_LASER_H
#define DISPERSION_LASER_H

#include "dispersion.h"

class DispersionLaser : public Dispersion
{
private:
    bool change_direction;

public:
    DispersionLaser();
    DispersionLaser(const bool &change_direction);
    int calculate_dispersion(const uint16_t &x) override;
    ~DispersionLaser();
};

#endif // DISPERSION_LASER_H