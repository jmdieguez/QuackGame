#include <memory>
#include <utility>
#include <functional>

#include "../map.h"
#include "../hitbox.h"
#include "../gun/gun.h"
#include "../gun/ak.h"
#include "../gun/shotgun.h"
#include "../../../common/position.h"
#include "../../../common/duck.h"

class GunController
{
protected:
    std::shared_ptr<Gun> gun;
    bool block_shooting_command;

public:
    GunController();

    GunType get_gun_type();
    TextureFigure get_gun_texture();
    uint16_t get_gun_angle(DuckStatus &status) const;
    Size get_gun_size() const;

    void finish_shooting();
    Position get_gun_position(Position &position, Size &size, DuckStatus &status) const;
    void discard_gun(std::map<uint8_t, std::shared_ptr<Gun>> &guns, Position &position, Size &size, DuckStatus &status);
    bool drop_grenade(DuckStatus &status);
    bool drop_banana(DuckStatus &status);
    void pick_up(std::map<uint8_t, std::shared_ptr<Gun>> &guns, DuckStatus &status, const std::function<bool(const Hitbox &)> &func);
    void fire(DuckStatus &status, Position &position, Map &map, const std::function<void(const std::shared_ptr<Projectile> &)> &add_projectile);

    ~GunController();
};