#include "defminvalue.h"
#include "shotgun.h"
#include "projectile/projectilegun.h"

#define VELOCITY 10
#define MAX_AMMO 2
#define MAX_SHOT 6
#define MIN_DISTANCE 7
#define MAX_DISTANCE 9
#define TIME_TO_SHOOT 20

#define GUN_WIDTH 25
#define GUN_HEIGHT 10

#define HORIZONTAL_Y 15
#define HORIZONTAL_RIGHT 8
#define HORIZONTAL_LEFT 0

#define VERTICAL_RIGHT -1
#define VERTICAL_LEFT 8

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

Shotgun::Shotgun(const uint16_t &pos_x, const uint16_t &pos_y) : Gun(GunType::Shotgun, Position(pos_x, pos_y), Size(GUN_WIDTH, GUN_HEIGHT)), GunAmmo(MAX_AMMO),
                                                                 position_gun(HORIZONTAL_Y, HORIZONTAL_RIGHT, HORIZONTAL_LEFT, VERTICAL_RIGHT, VERTICAL_LEFT),
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
    auto direction = get_direction(looking_right, looking_up);
    std::vector<std::shared_ptr<Projectile>> projectiles;

    uint16_t adjusted_pos_x = duck_position.x + (direction.first == 1 ? MIN_VALUE_RIGHT_DIRECTION_POS_X : MIN_VALUE_LEFT_DIRECTION_POS_X);
    Position projectile_position(adjusted_pos_x, duck_position.y);

    std::vector<std::shared_ptr<Dispersion>> dispersions = {
        std::make_shared<DispersionLow>(true),
        std::make_shared<DispersionLow>(),
        std::make_shared<DispersionMedium>(),
        std::make_shared<DispersionMedium>(true),
        std::make_shared<DispersionHigh>(),
        std::make_shared<DispersionHigh>(true)};

    for (auto &dispersion : dispersions)
        projectiles.push_back(std::make_shared<ProjectileGun>(ProjectileType::CowboyBullet, projectile_position, direction, VELOCITY, MAX_DISTANCE, dispersion));

    need_reload = true;
    block_shoot = true;
    return std::make_optional(std::make_pair(projectiles, duck_position));
}

Position Shotgun::get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up)
{
    return position_gun.get_position(height_duck, duck, looking_right, looking_up);
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
