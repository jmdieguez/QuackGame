
#include "gun.h"
#include "gunammo.h"
#include "dispersion/dispersionmedium.h"
#include "dispersion/dispersionlow.h"
#include "moveback.h"
#include "positiongun.h"
#include "projectile/projectilelaser.h"

class LaserRifle : public Gun, public GunAmmo, protected MoveBack
{
private:
    PositionGun position_gun;
    uint8_t time_shooting;
    uint8_t delay_shooting;

    bool random();

public:
    explicit LaserRifle(const uint16_t &id, const Position &position);
    std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> shoot(DuckStatus &status, const Position &duck_position) override;
    Position get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up) override;
    void check_reset();
    ~LaserRifle();
};
