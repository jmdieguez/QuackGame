#include "gun.h"
#include "gunammo.h"

class DuelingPistol : public Gun, public GunAmmo
{
private:
public:
    explicit DuelingPistol(uint16_t pos_x, uint16_t pos_y);
    std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> shoot(bool &looking_right, bool &looking_up, const Position &duck_position) override;
    ~DuelingPistol();
};