#include "gun.h"
#include "gunammo.h"
#include "dispersion/dispersionmedium.h"
#include "positiongun.h"

class DuelingPistol : public Gun, public GunAmmo
{
private:
    PositionGun position_gun;
    bool random();

public:
    explicit DuelingPistol(const uint16_t &pos_x, const uint16_t &pos_y);
    std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> shoot(bool &looking_right, bool &looking_up, const Position &duck_position) override;
    Position get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up) override;
    ~DuelingPistol();
};