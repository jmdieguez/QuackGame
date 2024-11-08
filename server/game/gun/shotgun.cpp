#define VELOCITY 10
#define MAX_AMMO 2
#define MAX_SHOT 6
#define MIN_DISTANCE 7
#define MAX_DISTANCE 9

#include "defminvalue.h"
#include "shotgun.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Shotgun::Shotgun(uint16_t pos_x, uint16_t pos_y) : Gun(GunType::Shotgun, pos_x, pos_y), GunAmmo(MAX_AMMO)
{
}

std::optional<std::pair<std::vector<Projectile>, Position>> Shotgun::shoot(bool &looking_right, bool &looking_up, const Position &duck_position)
{
    if (!have_ammo())
        return std::nullopt;
    reduce_ammo();
    std::vector<std::pair<int, int>> directions;
    std::vector<Projectile> projectiles;
    if (looking_right)
        directions = {{1, 0}, {1, 1}, {1, -1}, {1, 3}, {1, 2}, {1, -2}};
    if (!looking_right)
        directions = {{-1, 0}, {-1, 1}, {-1, -1}, {-1, 3}, {-1, 2}, {-1, -2}};
    if (looking_up)
        directions = {{0, -1}, {1, -1}, {-1, -1}, {0, -1}, {1, -1}, {-1, -1}};

    for (auto dir : directions)
    {
        uint16_t adjusted_pos_x = duck_position.pos_x + (dir.first == 1 ? MIN_VALUE_RIGHT_DIRECTION_POS_X : MIN_VALUE_LEFT_DIRECTION_POS_X);
        Position projectile_position(adjusted_pos_x, duck_position.pos_y);
        Projectile projectile(ProjectileType::CowboyBullet, projectile_position, dir, MAX_DISTANCE, VELOCITY);
        projectiles.push_back(projectile);
    }

    std::pair<std::vector<Projectile>, Position> result(projectiles, duck_position);
    return std::optional<std::pair<std::vector<Projectile>, Position>>(result);
}

Shotgun::~Shotgun()
{
}
