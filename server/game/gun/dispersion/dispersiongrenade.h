#include "dispersion.h"

class DispersionGrenade : public Dispersion
{
private:
public:
    DispersionGrenade();
    int calculate_dispersion(const uint16_t &x) override;
    ~DispersionGrenade();
};
