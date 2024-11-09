#
#include <utility>
#include <cstdint>
#include "../../../common/position.h"
#include "../../../common/snapshots.h"
#include "projectile/projectile.h"
#include "gun.h"
#include "gunammo.h"

class Grenade : public Gun, public GunAmmo
{
private:
    bool start_explosion_state;
    uint8_t time_explosion;

public:
    explicit Grenade(const uint16_t &pos_x, const uint16_t &pos_y);
    std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> shoot(bool &looking_right, bool &looking_up, const Position &duck_position) override;
    std::shared_ptr<Projectile> get_projectile(bool &looking_right, bool &looking_up);
    ~Grenade();
};
