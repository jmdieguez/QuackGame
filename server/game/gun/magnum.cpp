#include "magnum.h"
#include "defminvalue.h"
#include "projectile/projectilegun.h"

#define VELOCITY 10
#define MAX_AMMO 6
#define MAX_DISTANCE 20
#define DISPERSION_VALUE 1
#define BACK 5
#define WIDTH 26
#define HEIGHT 16

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Magnum::Magnum(const uint16_t &pos_x, const uint16_t &pos_y) : Gun(GunType::Magnum, Position(pos_x, pos_y), Size(WIDTH, HEIGHT)), GunAmmo(MAX_AMMO)
{
}

std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> Magnum::shoot(bool &looking_right, bool &looking_up, const Position &duck_position)
{
    if (!have_ammo())
        return std::nullopt;
    std::pair<int, int> directions = get_directions(looking_right, looking_up);
    reduce_ammo();
    apply_dispersion(directions, DISPERSION_VALUE);
    uint16_t adjusted_pos_x = duck_position.pos_x + (directions.first == 1 ? MIN_VALUE_RIGHT_DIRECTION_POS_X : MIN_VALUE_LEFT_DIRECTION_POS_X);
    Position projectile_position(adjusted_pos_x, duck_position.pos_y);
    std::vector<std::shared_ptr<Projectile>> projectiles;
    ProjectileType type = ProjectileType::CowboyBullet;
    projectiles.push_back(std::make_shared<ProjectileGun>(type, projectile_position, directions, VELOCITY, MAX_DISTANCE));
    Position new_position = move_back(duck_position, looking_right, BACK);
    std::pair<std::vector<std::shared_ptr<Projectile>>, Position> result(projectiles, new_position);
    return std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>>(result);
}

Magnum::~Magnum()
{
}