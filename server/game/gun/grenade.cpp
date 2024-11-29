#include "grenade.h"
#include "projectile/projectilegrenade.h"

#define MAX_DISTANCE 10
#define TIME_EXPLOSION 100

#define GUN_WIDTH 15
#define GUN_HEIGHT 15

#define PROJECTILE_WIDTH 15
#define PROJECTILE_HEIGHT 15

#define HORIZONTAL_Y 3
#define HORIZONTAL_RIGHT -10
#define HORIZONTAL_LEFT 10

#define VERTICAL_RIGHT -10
#define VERTICAL_LEFT 6

#define LOOKING_UP_RIGHT_OFFSET_X 0
#define LOOKING_UP_LEFT_OFFSET_X 18

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Grenade::Grenade(const uint16_t &id, const Position &position) : Gun(id, GunType::Grenade, Position(position), Size(GUN_WIDTH, GUN_HEIGHT), TextureFigure::GrenadeFigure),
                                                                 start_explosion_state(false), time_explosion(TIME_EXPLOSION)
{
}

std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> Grenade::shoot(DuckStatus &status, const Position &duck_position)
{
    if (start_explosion_state)
        return std::nullopt;
    start_explosion_state = true;
    std::vector<std::shared_ptr<Projectile>> projectiles;
    projectile_grenade = std::make_shared<ProjectileGrenade>(status, duck_position);
    projectiles.push_back(projectile_grenade);
    return std::make_optional(std::make_pair(projectiles, duck_position));
}
Position Grenade::get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up)
{
    (void)height_duck;
    (void)looking_up;
    uint16_t pos_x = duck.x + (looking_right ? HORIZONTAL_RIGHT : HORIZONTAL_LEFT);
    uint16_t pos_y = duck.y + HORIZONTAL_Y;
    return Position(pos_x, pos_y);
}

bool Grenade::throw_grenade(bool &looking_right)
{
    if (!start_explosion_state)
        return false;
    projectile_grenade->throw_grenade(looking_right);
    return true;
}

Grenade::~Grenade()
{
}
