#ifndef DISPERSION_HIGH_H
#define DISPERSION_HIGH_H

#include "dispersion.h"

class DispersionHigh : public Dispersion
{
private:
    bool change_direction;

public:
    DispersionHigh();
    DispersionHigh(const bool &change_direction);
    int calculate_dispersion(const uint16_t &x) override;
    ~DispersionHigh();
};

#endif // DISPERSION_HIGH_H