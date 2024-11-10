#ifndef DISPERSION_LOW_H
#define DISPERSION_LOW_H

#include "dispersion.h"

class DispersionLow : public Dispersion
{
private:
    bool change_direction;

public:
    DispersionLow();
    DispersionLow(const bool &change_direction);
    int calculate_dispersion(const uint16_t &x) override;
    ~DispersionLow();
};

#endif // DISPERSION_LOW_H