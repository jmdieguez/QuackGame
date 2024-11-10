#ifndef DISPERSION_MEDIUM_H
#define DISPERSION_MEDIUM_H

#include "dispersion.h"

class DispersionMedium : public Dispersion
{
private:
    bool change_direction;

public:
    DispersionMedium();
    DispersionMedium(const bool &change_direction);
    int calculate_dispersion(const uint16_t &x) override;
    ~DispersionMedium();
};

#endif // DISPERSION_MEDIUM_H