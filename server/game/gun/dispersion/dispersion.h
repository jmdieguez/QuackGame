#ifndef DISPERSION_H
#define DISPERSION_H

#include <random>

class Dispersion
{
private:
public:
    Dispersion() {};

    virtual int calculate_dispersion(const uint16_t &x) = 0;

    virtual ~Dispersion() = default;
};

#endif // DISPERSION_H