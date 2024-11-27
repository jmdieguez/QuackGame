#include "sniper.h"
#include "defminvalue.h"
#include "projectile/projectilegun.h"

#define VELOCITY 10
#define MAX_AMMO 3
#define MAX_DISTANCE 20
#define TIME_TO_SHOOT 20
#define TIME_TO_REALOAD 5

#define GUN_WIDTH 20
#define GUN_HEIGHT 10

#define PROJECTILE_WIDTH 8
#define PROJECTILE_HEIGHT 8

#define HORIZONTAL_Y 3
#define HORIZONTAL_RIGHT 6
#define HORIZONTAL_LEFT -10

#define VERTICAL_RIGHT -10
#define VERTICAL_LEFT 6

#define LOOKING_UP_RIGHT_OFFSET_X -3
#define LOOKING_UP_LEFT_OFFSET_X 15

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

void Sniper::reset()
{
    need_reload = false;
    time_to_shoot = TIME_TO_SHOOT;
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/
Sniper::Sniper(const uint16_t &id, const Position &position) : Gun(id, GunType::Sniper, Position(position), Size(GUN_WIDTH, GUN_HEIGHT), TextureFigure::SniperFigure),
                                                               GunAmmo(MAX_AMMO),
                                                               position_gun(HORIZONTAL_Y, HORIZONTAL_RIGHT, HORIZONTAL_LEFT, VERTICAL_RIGHT, VERTICAL_LEFT),
                                                               time_to_reaload(TIME_TO_REALOAD), time_to_shoot(TIME_TO_SHOOT), need_reload(false), block_shoot(false)
{
}

std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> Sniper::shoot(DuckStatus &status, const Position &duck_position)
{
    if (!have_ammo())
        return std::nullopt;
    if (need_reload)
    {
        if (time_to_reaload)
        {
            time_to_reaload--;
            block_shoot = false;
            return std::nullopt;
        }
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
    auto direction = get_direction(status.looking_right, status.looking_up);
    reduce_ammo();
    uint16_t adjusted_pos_x = duck_position.x + (status.looking_up ? (status.looking_right ? LOOKING_UP_RIGHT_OFFSET_X : LOOKING_UP_LEFT_OFFSET_X) : (status.looking_right ? ((DUCK_DEFAULT_WIDTH + 1) * direction.first) : (-1)));
    uint16_t adjusted_pos_y = duck_position.y + (status.looking_up ? -GUN_WIDTH : HORIZONTAL_Y);
    Position projectile_position(adjusted_pos_x, adjusted_pos_y);
    Hitbox hitbox(projectile_position, Size(PROJECTILE_WIDTH, PROJECTILE_HEIGHT));
    std::vector<std::shared_ptr<Projectile>> projectiles;
    ProjectileType type = ProjectileType::CowboyBullet;
    projectiles.push_back(std::make_shared<ProjectileGun>(type, TextureFigure::CowboyBullet, hitbox, direction, VELOCITY, MAX_DISTANCE));
    need_reload = true;
    block_shoot = true;
    time_to_reaload = TIME_TO_REALOAD;
    std::pair<std::vector<std::shared_ptr<Projectile>>, Position> result(projectiles, duck_position);
    return std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>>(result);
}

Position Sniper::get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up)
{
    return position_gun.get_position(height_duck, duck, looking_right, looking_up);
}

bool Sniper::is_block_shoot() const
{
    return block_shoot;
}

void Sniper::check_reset()
{
    if (time_to_shoot > 0 && time_to_shoot != TIME_TO_SHOOT)
    {
        time_to_shoot = TIME_TO_SHOOT;
    }
    if (time_to_reaload > 0 && time_to_reaload != TIME_TO_REALOAD)
    {
        time_to_reaload = TIME_TO_REALOAD;
    }
}

Sniper::~Sniper()
{
}