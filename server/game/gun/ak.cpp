#include <cstdlib>
#include <ctime>

#include "ak.h"
#include "defminvalue.h"
#include "projectile/projectilegun.h"

#define VELOCITY 15
#define MAX_AMMO 30
#define MAX_DISTANCE 13
#define TIME_SHOOTING 60
#define DELAY_SHOOTING 2
#define START_DISPERSION 55
#define START_MORE_DISPERSION 45
#define VALUE_DISPERSION 1
#define VALUE_MORE_DISPERSION 2
#define BACK 3

#define GUN_WIDTH 25
#define GUN_HEIGHT 10

#define DUCK_WITH_GUN_Y_DIRECTION 15
#define DUCK_WITH_GUN_RIGHT_DIRECTION 10
#define DUCK_WITH_GUN_LEFT_DIRECTION 0

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

bool AK::random()
{
    std::srand(std::time(nullptr));
    return std::rand() % 2 == 0;
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

AK::AK(const uint16_t &pos_x, const uint16_t &pos_y) : Gun(GunType::AK, Position(pos_x, pos_y), Size(GUN_WIDTH, GUN_HEIGHT)), GunAmmo(MAX_AMMO), time_shooting(TIME_SHOOTING), delay_shooting(DELAY_SHOOTING)
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
    auto direction = get_direction(looking_right, looking_up);
    reduce_ammo();
    std::shared_ptr<Dispersion> dispersion = nullptr;
    if (time_shooting < START_DISPERSION)
        dispersion = std::make_shared<DispersionLow>(random());
    if (time_shooting < START_MORE_DISPERSION)
        dispersion = std::make_shared<DispersionMedium>(random());
    uint16_t adjusted_pos_x = duck_position.x + (direction.first > 0 ? MIN_VALUE_RIGHT_DIRECTION_POS_X : MIN_VALUE_LEFT_DIRECTION_POS_X);
    Position projectile_position(adjusted_pos_x, duck_position.y);
    std::vector<std::shared_ptr<Projectile>> projectiles;
    projectiles.push_back(std::make_shared<ProjectileGun>(ProjectileType::CowboyBullet, projectile_position, direction, VELOCITY, MAX_DISTANCE, dispersion));
    Position new_position = move_back(duck_position, looking_right, BACK);
    delay_shooting = DELAY_SHOOTING;
    time_shooting--;
    return std::make_optional(std::make_pair(projectiles, new_position));
}

Position AK::get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right)
{
    (void)height_duck;
    (void)looking_right;
    uint16_t pos_x = duck.x + (looking_right ? DUCK_WITH_GUN_RIGHT_DIRECTION : DUCK_WITH_GUN_LEFT_DIRECTION);
    uint16_t pos_y = duck.y + DUCK_WITH_GUN_Y_DIRECTION;
    return Position(pos_x, pos_y);
}

void AK::check_reset()
{
    time_shooting = TIME_SHOOTING;
    delay_shooting = DELAY_SHOOTING;
};

AK::~AK()
{
}
