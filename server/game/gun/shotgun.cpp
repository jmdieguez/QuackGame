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

#define PROJECTILE_WIDTH 8
#define PROJECTILE_HEIGHT 8

#define HORIZONTAL_Y 5
#define HORIZONTAL_RIGHT 5
#define HORIZONTAL_LEFT -14

#define VERTICAL_RIGHT -12
#define VERTICAL_LEFT 3

#define LOOKING_UP_RIGHT_OFFSET_X 0
#define LOOKING_UP_LEFT_OFFSET_X 18

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

Shotgun::Shotgun(const uint16_t &id, const Position &position) : Gun(id, GunType::Shotgun, Position(position), Size(GUN_WIDTH, GUN_HEIGHT), TextureFigure::ShotgunFigure),
                                                                 GunAmmo(MAX_AMMO),
                                                                 position_gun(HORIZONTAL_Y, HORIZONTAL_RIGHT, HORIZONTAL_LEFT, VERTICAL_RIGHT, VERTICAL_LEFT),
                                                                 time_to_shoot(TIME_TO_SHOOT),
                                                                 need_reload(false), block_shoot(false)
{
}

std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> Shotgun::shoot(DuckStatus &status, const Position &duck_position)
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
    auto direction = get_direction(status.looking_right, status.looking_up);
    std::vector<std::shared_ptr<Projectile>> projectiles;

    uint16_t adjusted_pos_x = duck_position.x + (status.looking_up ? (status.looking_right ? LOOKING_UP_RIGHT_OFFSET_X : LOOKING_UP_LEFT_OFFSET_X) : (status.looking_right ? ((DUCK_DEFAULT_WIDTH + 1) * direction.first) : (-1)));
    uint16_t adjusted_pos_y = duck_position.y + (status.looking_up ? -GUN_WIDTH : HORIZONTAL_Y);
    Position projectile_position(adjusted_pos_x, adjusted_pos_y);
    Hitbox hitbox(projectile_position, Size(PROJECTILE_WIDTH, PROJECTILE_HEIGHT));
    std::vector<std::shared_ptr<Dispersion>> dispersions = {
        std::make_shared<DispersionLow>(true),
        std::make_shared<DispersionLow>(),
        std::make_shared<DispersionMedium>(),
        std::make_shared<DispersionMedium>(true),
        std::make_shared<DispersionHigh>(),
        std::make_shared<DispersionHigh>(true)};

    for (auto &dispersion : dispersions)
        projectiles.push_back(std::make_shared<ProjectileGun>(ProjectileType::CowboyBullet, TextureFigure::CowboyBullet, hitbox, direction, VELOCITY, MAX_DISTANCE, dispersion));

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
