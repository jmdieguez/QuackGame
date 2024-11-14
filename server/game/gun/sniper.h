#include "gun.h"
#include "gunammo.h"
#include "positiongun.h"

class Sniper : public Gun, public GunAmmo
{
private:
    PositionGun position_gun;
    uint8_t time_to_reaload;
    uint8_t time_to_shoot;
    bool need_reload;
    bool block_shoot;

    void reset();

public:
    explicit Sniper(const uint16_t &id, const Position &position);
    std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> shoot(bool &looking_right, bool &looking_up, const Position &duck_position) override;
    Position get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up) override;
    bool is_block_shoot() const;
    void check_reset();
    ~Sniper();
};
