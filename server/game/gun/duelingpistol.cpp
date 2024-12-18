#include <cstdlib>
#include <ctime>

#include "duelingpistol.h"
#include "defminvalue.h"
#include "projectile/projectilegun.h"

#define GUN_WIDTH 20
#define GUN_HEIGHT 10

#define PROJECTILE_WIDTH 8
#define PROJECTILE_HEIGHT 8

#define HORIZONTAL_Y 3
#define HORIZONTAL_RIGHT 10
#define HORIZONTAL_LEFT -14

#define VERTICAL_RIGHT -10
#define VERTICAL_LEFT 6

#define LOOKING_UP_RIGHT_OFFSET_X 0
#define LOOKING_UP_LEFT_OFFSET_X 18

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

bool DuelingPistol::random()
{
    std::srand(std::time(nullptr));
    return std::rand() % 2 == 0;
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

DuelingPistol::DuelingPistol(const uint16_t &id, const Position &position) : Gun(id, GunType::DuelingPistol, Position(position), Size(GUN_WIDTH, GUN_HEIGHT), TextureFigure::DuelingPistolFigure),
                                                                             GunAmmo(Config::getInstance()["gun"]["ammo"]["dueling_pistol"].as<int>()),
                                                                             position_gun(HORIZONTAL_Y, HORIZONTAL_RIGHT, HORIZONTAL_LEFT, VERTICAL_RIGHT, VERTICAL_LEFT)
{
}

std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> DuelingPistol::shoot(DuckStatus &status, const Position &duck_position)
{
    if (!have_ammo())
        return std::nullopt;
    reduce_ammo();
    auto direction = get_direction(status.looking_right, status.looking_up);
    uint16_t adjusted_pos_x = duck_position.x + (status.looking_up ? (status.looking_right ? LOOKING_UP_RIGHT_OFFSET_X : LOOKING_UP_LEFT_OFFSET_X) : (status.looking_right ? ((DUCK_DEFAULT_WIDTH + 1) * direction.first) : (-1)));
    uint16_t adjusted_pos_y = duck_position.y + (status.looking_up ? -GUN_WIDTH : HORIZONTAL_Y);
    Position projectile_position(adjusted_pos_x, adjusted_pos_y);
    std::shared_ptr<Dispersion> dispersion = std::make_shared<DispersionMedium>(random());
    Hitbox hitbox(projectile_position, Size(PROJECTILE_WIDTH, PROJECTILE_HEIGHT));
    int velocity = Config::getInstance()["gun"]["velocity_projectile"]["dueling_pistol"].as<int>();
    int max_distance = Config::getInstance()["gun"]["scope"]["dueling_pistol"].as<int>();
    std::vector<std::shared_ptr<Projectile>> projectiles = {
        std::make_shared<ProjectileGun>(ProjectileType::CowboyBullet, TextureFigure::CowboyBullet, hitbox, direction, velocity, max_distance, dispersion)};
    return std::make_optional(std::make_pair(projectiles, duck_position));
}

Position DuelingPistol::get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up)
{
    return position_gun.get_position(height_duck, duck, looking_right, looking_up);
}

DuelingPistol::~DuelingPistol()
{
}
