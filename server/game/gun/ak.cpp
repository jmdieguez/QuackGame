#include "ak.h"
#include "defminvalue.h"
#include "projectile/projectilegun.h"

#define VELOCITY 10
#define MAX_AMMO 30
#define MAX_DISTANCE 13
#define TIME_SHOOTING 60
#define DELAY_SHOOTING 3
#define START_DISPERSION 50
#define START_MORE_DISPERSION 45
#define VALUE_DISPERSION 1
#define VALUE_MORE_DISPERSION 2
#define BACK 3

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

AK::AK(uint16_t pos_x, uint16_t pos_y) : Gun(GunType::AK, pos_x, pos_y), GunAmmo(MAX_AMMO), time_shooting(TIME_SHOOTING), delay_shooting(DELAY_SHOOTING)
{
}

std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> AK::shoot(bool &looking_right, bool &looking_up, const Position &duck_position)
{
    if (!have_ammo())
        return std::nullopt;
    if (time_shooting != TIME_SHOOTING && delay_shooting)
    {
        delay_shooting--;
        return std::nullopt;
    }
    std::pair<int, int> directions = get_directions(looking_right, looking_up);
    reduce_ammo();
    int value_dispersion = 0;
    if (time_shooting < START_DISPERSION)
        value_dispersion = VALUE_DISPERSION;
    if (time_shooting < START_MORE_DISPERSION)
        value_dispersion = VALUE_MORE_DISPERSION;
    apply_dispersion(directions, value_dispersion);
    uint16_t adjusted_pos_x = duck_position.pos_x + (directions.first > 0 ? MIN_VALUE_RIGHT_DIRECTION_POS_X : MIN_VALUE_LEFT_DIRECTION_POS_X);
    Position projectile_position(adjusted_pos_x, duck_position.pos_y);
    std::vector<std::shared_ptr<Projectile>> projectiles;
    projectiles.push_back(std::make_shared<ProjectileGun>(ProjectileType::CowboyBullet, projectile_position, directions, VELOCITY, MAX_DISTANCE));
    Position new_position = move_back(duck_position, looking_right, BACK);
    delay_shooting = DELAY_SHOOTING;
    time_shooting--;
    std::pair<std::vector<std::shared_ptr<Projectile>>, Position> result(projectiles, new_position);
    return std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>>(result);
}

void AK::check_reset()
{
    time_shooting = TIME_SHOOTING;
    delay_shooting = DELAY_SHOOTING;
};

AK::~AK()
{
}
