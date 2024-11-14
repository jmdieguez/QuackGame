#include "cowboypistol.h"
#include "defminvalue.h"
#include "projectile/projectilegun.h"

#define VELOCITY 10
#define MAX_AMMO 6
#define MAX_DISTANCE 20

#define GUN_WIDTH 20
#define GUN_HEIGHT 10

#define HORIZONTAL_Y 3
#define HORIZONTAL_RIGHT 10
#define HORIZONTAL_LEFT -14

#define VERTICAL_RIGHT -10
#define VERTICAL_LEFT 6

#define LOOKING_UP_RIGHT_OFFSET_X 0
#define LOOKING_UP_LEFT_OFFSET_X 18

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

CowboyPistol::CowboyPistol(const uint16_t &id, const Position &position) : Gun(id, GunType::CowboyPistol, Position(position), Size(GUN_WIDTH, GUN_HEIGHT), TextureFigure::CowboyPistolFigure),
                                                                           GunAmmo(MAX_AMMO),
                                                                           position_gun(HORIZONTAL_Y, HORIZONTAL_RIGHT, HORIZONTAL_LEFT, VERTICAL_RIGHT, VERTICAL_LEFT)
{
}

std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> CowboyPistol::shoot(bool &looking_right, bool &looking_up, const Position &duck_position)
{
    if (!have_ammo())
        return std::nullopt;
    reduce_ammo();
    auto direction = get_direction(looking_right, looking_up);
    uint16_t adjusted_pos_x = duck_position.x + (looking_up ? (looking_right ? LOOKING_UP_RIGHT_OFFSET_X : LOOKING_UP_LEFT_OFFSET_X) : GUN_WIDTH * direction.first);
    uint16_t adjusted_pos_y = duck_position.y + (looking_up ? -GUN_WIDTH : VERTICAL_RIGHT);
    Position projectile_position(adjusted_pos_x, adjusted_pos_y);
    std::vector<std::shared_ptr<Projectile>> projectiles = {
        std::make_shared<ProjectileGun>(ProjectileType::CowboyBullet, projectile_position, direction, VELOCITY, MAX_DISTANCE)};
    return std::make_optional(std::make_pair(projectiles, duck_position));
}
Position CowboyPistol::get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up)
{
    return position_gun.get_position(height_duck, duck, looking_right, looking_up);
}
CowboyPistol::~CowboyPistol()
{
}