#include <cstdlib>
#include <ctime>

#include "ak.h"
#include "defminvalue.h"
#include "projectile/projectilegun.h"

#define VELOCITY 20
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

#define HORIZONTAL_Y 5
#define HORIZONTAL_RIGHT 5
#define HORIZONTAL_LEFT -14

#define VERTICAL_RIGHT -12
#define VERTICAL_LEFT 3

#define LOOKING_UP_RIGHT_OFFSET_X 0
#define LOOKING_UP_LEFT_OFFSET_X 18

#define SPECIAL_OFFSET_SHOOT_AK 6
#define SPECIAL_OFFSET_X_AK 5

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

AK::AK(const uint16_t &id, const Position &position) : Gun(id, GunType::AK, Position(position), Size(GUN_WIDTH, GUN_HEIGHT), TextureFigure::AKFigure),
                                                       GunAmmo(MAX_AMMO),
                                                       position_gun(HORIZONTAL_Y, HORIZONTAL_RIGHT, HORIZONTAL_LEFT, VERTICAL_RIGHT, VERTICAL_LEFT),
                                                       time_shooting(TIME_SHOOTING), delay_shooting(DELAY_SHOOTING)
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
    uint16_t adjusted_pos_x = duck_position.x + (looking_up ? (looking_right ? LOOKING_UP_RIGHT_OFFSET_X : LOOKING_UP_LEFT_OFFSET_X) : (GUN_WIDTH + SPECIAL_OFFSET_SHOOT_AK) * direction.first);
    uint16_t adjusted_pos_y = duck_position.y + (looking_up ? -GUN_WIDTH : (VERTICAL_RIGHT + SPECIAL_OFFSET_X_AK));
    Position projectile_position(adjusted_pos_x, adjusted_pos_y);
    std::vector<std::shared_ptr<Projectile>> projectiles;
    projectiles.push_back(std::make_shared<ProjectileGun>(ProjectileType::CowboyBullet, TextureFigure::CowboyBullet, projectile_position, direction, VELOCITY, MAX_DISTANCE, dispersion));
    Position new_position = move_back(duck_position, looking_right, BACK);
    delay_shooting = DELAY_SHOOTING;
    time_shooting--;
    return std::make_optional(std::make_pair(projectiles, new_position));
}

Position AK::get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up)
{
    return position_gun.get_position(height_duck, duck, looking_right, looking_up);
}

void AK::check_reset()
{
    time_shooting = TIME_SHOOTING;
    delay_shooting = DELAY_SHOOTING;
}

AK::~AK()
{
}
