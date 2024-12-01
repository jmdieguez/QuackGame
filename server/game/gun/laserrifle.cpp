#include <cstdlib>
#include <ctime>

#include "laserrifle.h"
#include "defminvalue.h"
#include "projectile/projectilegun.h"

#define MAX_DISTANCE 13
#define TIME_SHOOTING 60
#define DELAY_SHOOTING 2
#define START_DISPERSION 55
#define START_MORE_DISPERSION 45
#define VALUE_DISPERSION 1
#define VALUE_MORE_DISPERSION 2

#define GUN_WIDTH 25
#define GUN_HEIGHT 10

#define PROJECTILE_WIDTH 8
#define PROJECTILE_HEIGHT 8

#define HORIZONTAL_Y 5
#define HORIZONTAL_RIGHT 5
#define HORIZONTAL_LEFT -14

#define VERTICAL_RIGHT -12
#define VERTICAL_LEFT 3

#define LOOKING_UP_RIGHT_OFFSET_X -6
#define LOOKING_UP_LEFT_OFFSET_X 18

#define SPECIAL_OFFSET_SHOOT_AK 6
#define SPECIAL_OFFSET_X_AK 5

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

bool LaserRifle::random()
{
    std::srand(std::time(nullptr));
    return std::rand() % 2 == 0;
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

LaserRifle::LaserRifle(const uint16_t &id, const Position &position) : Gun(id, GunType::LaserRifle, Position(position), Size(GUN_WIDTH, GUN_HEIGHT), TextureFigure::LaserRifleFigure),
                                                                       GunAmmo(Config::getInstance()["gun"]["ammo"]["laser_rifle"].as<int>()),
                                                                       position_gun(HORIZONTAL_Y, HORIZONTAL_RIGHT, HORIZONTAL_LEFT, VERTICAL_RIGHT, VERTICAL_LEFT),
                                                                       time_shooting(TIME_SHOOTING), delay_shooting(DELAY_SHOOTING)
{
}

std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> LaserRifle::shoot(DuckStatus &status, const Position &duck_position)
{
    if (!have_ammo())
        return std::nullopt;
    if (time_shooting != TIME_SHOOTING && delay_shooting)
    {
        delay_shooting--;
        return std::nullopt;
    }
    auto direction = get_direction(status.looking_right, status.looking_up);
    reduce_ammo();
    std::shared_ptr<Dispersion> dispersion = nullptr;
    if (time_shooting < START_DISPERSION)
        dispersion = std::make_shared<DispersionLow>(random());
    if (time_shooting < START_MORE_DISPERSION)
        dispersion = std::make_shared<DispersionMedium>(random());
    uint16_t adjusted_pos_x = duck_position.x + (status.looking_up ? (status.looking_right ? LOOKING_UP_RIGHT_OFFSET_X : LOOKING_UP_LEFT_OFFSET_X) : (status.looking_right ? ((DUCK_DEFAULT_WIDTH + 1) * direction.first) : (-1)));
    uint16_t adjusted_pos_y = duck_position.y + (status.looking_up ? -GUN_WIDTH : HORIZONTAL_Y);
    Position projectile_position(adjusted_pos_x, adjusted_pos_y);
    std::vector<std::shared_ptr<Projectile>> projectiles;
    Hitbox hitbox(projectile_position, Size(PROJECTILE_WIDTH, PROJECTILE_HEIGHT));
    int velocity = Config::getInstance()["gun"]["velocity_projectile"]["laser_rifle"].as<int>();
    projectiles.push_back(std::make_shared<ProjectileLaser>(ProjectileType::CowboyBullet, TextureFigure::LaserRifleBullet, hitbox, direction, velocity, MAX_DISTANCE, dispersion));
    delay_shooting = DELAY_SHOOTING;
    time_shooting--;
    return std::make_optional(std::make_pair(projectiles, duck_position));
}

Position LaserRifle::get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up)
{
    return position_gun.get_position(height_duck, duck, looking_right, looking_up);
}

void LaserRifle::check_reset()
{
    time_shooting = TIME_SHOOTING;
    delay_shooting = DELAY_SHOOTING;
}
LaserRifle::~LaserRifle()
{
}
