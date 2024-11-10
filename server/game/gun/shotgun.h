
#include "gun.h"
#include "gunammo.h"
#include "dispersion/dispersionlow.h"
#include "dispersion/dispersionmedium.h"
#include "dispersion/dispersionhigh.h"
#include "positiongun.h"

class Shotgun : public Gun, public GunAmmo
{
private:
    PositionGun position_gun;
    uint8_t time_to_shoot;
    bool need_reload;
    bool block_shoot;

    void reset();

public:
    explicit Shotgun(const uint16_t &pos_x, const uint16_t &pos_y);
    std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> shoot(bool &looking_right, bool &looking_up, const Position &duck_position) override;
    Position get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up) override;
    bool is_block_shoot() const;
    void check_reset();
    ~Shotgun();
};
