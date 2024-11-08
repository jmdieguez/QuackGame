#include "magnum.h"

#include <random>

#include "defminvalue.h"

#define VELOCITY 10
#define MAX_AMMO 6
#define MAX_DISTANCE 20

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

void Magnum::apply_dispersion(std::pair<int, int> &directions)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    if (directions.first > 0)
    {
        std::uniform_real_distribution<> dist(0, 1);
        uint16_t random_number = dist(gen);
        directions.first += random_number;
    }
    else
    {
        std::uniform_real_distribution<> dist(-1, 0);
        uint16_t random_number = dist(gen);
        if (directions.first < 0)
            directions.first += random_number;
        if (directions.second < 0)
            directions.second += random_number;
    }
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Magnum::Magnum(uint16_t pos_x, uint16_t pos_y) : ammo(MAX_AMMO)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

bool Magnum::have_ammo()
{
    return ammo > 0;
}

std::pair<Projectile, Position> Magnum::shoot(bool &looking_right, bool &looking_up, const Position &duck_position)
{
    std::pair<int, int> directions = getDirections(looking_right, looking_up);
    ammo--;
    // apply_dispersion(directions);
    uint16_t adjusted_pos_x = duck_position.pos_x + (directions.first == 1 ? MIN_VALUE_RIGHT_DIRECTION_POS_X : MIN_VALUE_LEFT_DIRECTION_POS_X);
    Position projectile_position(adjusted_pos_x, duck_position.pos_y);
    Projectile projectile(ProjectileType::CowboyBullet, projectile_position, directions, MAX_DISTANCE, VELOCITY);
    std::pair<Projectile, Position> result(projectile, duck_position);
    return result;
}

GunNoEquippedSnapshot Magnum::get_status()
{
    return GunNoEquippedSnapshot(GunType::Magnum, pos_x, pos_y);
}

GunType Magnum::get_type()
{
    return GunType::Magnum;
}

Magnum::~Magnum()
{
}