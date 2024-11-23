#include "grenade.h"
#include "projectile/projectilegrenade.h"

#define MAX_DISTANCE 10
#define TIME_EXPLOSION 100

#define GUN_WIDTH 15
#define GUN_HEIGHT 15

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
                                                                 position_gun(HORIZONTAL_Y, HORIZONTAL_RIGHT, HORIZONTAL_LEFT, VERTICAL_RIGHT, VERTICAL_LEFT),
                                                                 start_explosion_state(false), time_explosion(TIME_EXPLOSION) {}

std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> Grenade::shoot(bool &looking_right, bool &looking_up, const Position &duck_position)
{
    (void)looking_right;
    (void)looking_up;
    (void)duck_position;
    start_explosion_state = true;
    return std::nullopt;
}

Position Grenade::get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up)
{
    (void)height_duck;
    (void)looking_up;
    uint16_t pos_x = duck.x + (looking_right ? HORIZONTAL_RIGHT : HORIZONTAL_LEFT);
    uint16_t pos_y = duck.y + HORIZONTAL_Y;
    return Position(pos_x, pos_y);
}

std::shared_ptr<Projectile> Grenade::get_projectile(bool &looking_right, bool &looking_up)
{
    (void)looking_up;
    std::pair<int, int> directions = looking_right ? std::make_pair(1, 0) : std::make_pair(-1, 0);
    return std::make_shared<ProjectileGrenade>(position, directions);
}

Grenade::~Grenade()
{
}
