
#include "gun.h"
#include "gunammo.h"
#include "dispersion.h"

class Shotgun : public Gun, public GunAmmo, protected Dispersion
{
private:
    uint8_t time_to_shoot;
    bool need_reload;
    bool block_shoot;
    void reset();

public:
    explicit Shotgun(uint16_t pos_x, uint16_t pos_y);
    std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> shoot(bool &looking_right, bool &looking_up, const Position &duck_position) override;
    bool is_block_shoot() const;
    void check_reset();
    ~Shotgun();
};
