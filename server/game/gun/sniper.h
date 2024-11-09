#include "gun.h"
#include "gunammo.h"

class Sniper : public Gun, public GunAmmo
{
private:
    uint8_t time_to_reaload;
    uint8_t time_to_shoot;
    bool need_reload;
    bool block_shoot;

    void reset();

public:
    explicit Sniper(uint16_t pos_x, uint16_t pos_y);
    std::optional<std::pair<std::vector<Projectile>, Position>> shoot(bool &looking_right, bool &looking_up, const Position &duck_position) override;
    bool is_block_shoot() const;
    void check_reset();
    ~Sniper();
};
