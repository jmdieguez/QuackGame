#include "pewpewlaser.h"
#include "defminvalue.h"
#include "projectile/projectilegun.h"

#define MAX_DISTANCE 38
#define MIN_DISTANCE 35

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

#define SPECIAL_OFFSET_X_PEWPEWLASER 3

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

PewPewLaser::PewPewLaser(const uint16_t &id, const Position &position) : Gun(id, GunType::PewPewLaser, Position(position), Size(GUN_WIDTH, GUN_HEIGHT), TextureFigure::PewPewLaserFigure),
                                                                         GunAmmo(Config::getInstance()["gun"]["ammo"]["pew_pew_laser"].as<int>()),
                                                                         position_gun(HORIZONTAL_Y, HORIZONTAL_RIGHT, HORIZONTAL_LEFT, VERTICAL_RIGHT, VERTICAL_LEFT)
{
}

std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> PewPewLaser::shoot(DuckStatus &status, const Position &duck_position)
{
    if (!have_ammo())
        return std::nullopt;
    auto direction = get_direction(status.looking_right, status.looking_up);
    reduce_ammo();
    std::vector<std::shared_ptr<Projectile>> projectiles;
    uint16_t adjusted_pos_x = duck_position.x + (status.looking_up ? (status.looking_right ? LOOKING_UP_RIGHT_OFFSET_X : LOOKING_UP_LEFT_OFFSET_X) : (status.looking_right ? ((DUCK_DEFAULT_WIDTH + 1) * direction.first) : (-1)));
    uint16_t adjusted_pos_y = duck_position.y + (status.looking_up ? -GUN_WIDTH : HORIZONTAL_Y);
    Position projectile_position(adjusted_pos_x, adjusted_pos_y);
    Hitbox hitbox(projectile_position, Size(PROJECTILE_WIDTH, PROJECTILE_HEIGHT));
    std::vector<std::shared_ptr<Dispersion>> dispersions = {
        nullptr,
        std::make_shared<DispersionHigh>(true),
        std::make_shared<DispersionHigh>()};
    int velocity = Config::getInstance()["gun"]["velocity_projectile"]["pew_pew_laser"].as<int>();
    for (auto &dispersion : dispersions)
        projectiles.push_back(std::make_shared<ProjectileGun>(ProjectileType::CowboyBullet, TextureFigure::CowboyBullet, hitbox, direction, velocity, MAX_DISTANCE, dispersion));

    return std::make_optional(std::make_pair(projectiles, duck_position));
}

Position PewPewLaser::get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up)
{
    return position_gun.get_position(height_duck, duck, looking_right, looking_up);
}

PewPewLaser::~PewPewLaser()
{
}
