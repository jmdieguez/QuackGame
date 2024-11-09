#
#include <utility>
#include <cstdint>
#include "../../../common/position.h"
#include "../../../common/snapshots.h"
#include "projectile.h"
#include "gun.h"
#include "gunammo.h"

class Grenade : public Gun, public GunAmmo
{
private:
    bool start_explosion_state;
    uint8_t time_explosion;

public:
    explicit Grenade(uint16_t pos_x, uint16_t pos_y);
    std::optional<std::pair<std::vector<Projectile>, Position>> shoot(bool &looking_right, bool &looking_up, const Position &duck_position) override;
    Projectile get_projectile(bool &looking_right, bool &looking_up);

    ~Grenade();
};
