#include "defminvalue.h"
#include "shotgun.h"
#include "projectile/projectilegun.h"

#define VELOCITY 10
#define MAX_AMMO 2
#define MAX_SHOT 6
#define MIN_DISTANCE 7
#define MAX_DISTANCE 9
#define TIME_TO_SHOOT 20
#define WIDTH 20
#define HEIGHT 10
/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

void Shotgun::reset()
{
    need_reload = false;
    time_to_shoot = TIME_TO_SHOOT;
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Shotgun::Shotgun(const uint16_t &pos_x, const uint16_t &pos_y) : Gun(GunType::Shotgun, Position(pos_x, pos_y), Size(WIDTH, HEIGHT)), GunAmmo(MAX_AMMO),
                                                                 time_to_shoot(TIME_TO_SHOOT),
                                                                 need_reload(false), block_shoot(false)
{
}

std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> Shotgun::shoot(bool &looking_right, bool &looking_up, const Position &duck_position)
{
    if (!have_ammo())
        return std::nullopt;
    if (need_reload)
    {
        block_shoot = true;
        need_reload = false;
        time_to_shoot = TIME_TO_SHOOT;
        return std::nullopt;
    }
    block_shoot = false;
    if (time_to_shoot)
    {
        time_to_shoot--;
        return std::nullopt;
    }
    reduce_ammo();
    std::pair<int, int> directions = get_directions(looking_right, looking_up);
    auto directions_shotgun = apply_dispersion_shotgun(directions);
    std::vector<std::shared_ptr<Projectile>> projectiles;
    for (auto dir : directions_shotgun)
    {
        uint16_t adjusted_pos_x = duck_position.x + (dir.first == 1 ? MIN_VALUE_RIGHT_DIRECTION_POS_X : MIN_VALUE_LEFT_DIRECTION_POS_X);
        Position projectile_position(adjusted_pos_x, duck_position.y);
        uint8_t distance = (dir.first == 1 && dir.second == 0) || (dir.first == -1 && dir.second == 0) ? MAX_DISTANCE : MIN_DISTANCE;
        ProjectileType type = ProjectileType::CowboyBullet;
        projectiles.push_back(std::make_shared<ProjectileGun>(type, projectile_position, dir, VELOCITY, distance));
    }
    need_reload = true;
    block_shoot = true;
    std::pair<std::vector<std::shared_ptr<Projectile>>, Position> result(projectiles, duck_position);
    return std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>>(result);
}
bool Shotgun::is_block_shoot() const
{
    return block_shoot;
}

void Shotgun::check_reset()
{
    if (time_to_shoot > 0)
        time_to_shoot = TIME_TO_SHOOT;
}

Shotgun::~Shotgun()
{
}
