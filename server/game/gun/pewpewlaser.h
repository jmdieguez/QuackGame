#include "gun.h"
#include "gunammo.h"
#include "dispersion.h"

class PewPewLaser : public Gun, public GunAmmo, protected Dispersion
{
private:
public:
    explicit PewPewLaser(const uint16_t &pos_x, const uint16_t &pos_y);
    std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> shoot(bool &looking_right, bool &looking_up, const Position &duck_position) override;
    ~PewPewLaser();
};
