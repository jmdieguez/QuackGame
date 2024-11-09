#include "gun.h"
#include "gunammo.h"
#include "dispersion.h"
#include "moveback.h"

class AK : public Gun, public GunAmmo, protected Dispersion, protected MoveBack
{
private:
    uint8_t time_shooting;
    uint8_t delay_shooting;

public:
    explicit AK(const uint16_t &pos_x, const uint16_t &pos_y);
    std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> shoot(bool &looking_right, bool &looking_up, const Position &duck_position) override;
    void check_reset();
    ~AK();
};
