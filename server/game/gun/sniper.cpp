#include "sniper.h"
#include "cowboypistol.h"
#include "defminvalue.h"

#define VELOCITY 10
#define MAX_AMMO 3
#define MAX_DISTANCE 20
#define TIME_TO_SHOOT 20
#define TIME_TO_REALOAD 5

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
Sniper::Sniper(uint16_t pos_x, uint16_t pos_y) : Gun(GunType::Sniper, pos_x, pos_y), GunAmmo(MAX_AMMO),
                                                 time_to_reaload(TIME_TO_REALOAD), time_to_shoot(TIME_TO_SHOOT), need_reload(false), block_shoot(false)
{
}

std::optional<std::pair<std::vector<Projectile>, Position>> Sniper::shoot(bool &looking_right, bool &looking_up, const Position &duck_position)
{
    if (!have_ammo())
        return std::nullopt;
    if (need_reload)
    {
        if (time_to_reaload)
        {
            time_to_reaload--;
            block_shoot = false;
            std::cout << "Desconte el tiempo de recarga y es: " << (int)time_to_reaload << std::endl;
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
        std::cout << "Desconte el tiempo de disparo y es: " << (int)time_to_shoot << std::endl;
        return std::nullopt;
    }
    std::pair<int, int> directions = get_directions(looking_right, looking_up);
    reduce_ammo();
    uint16_t adjusted_pos_x = duck_position.pos_x + (directions.first == 1 ? MIN_VALUE_RIGHT_DIRECTION_POS_X : MIN_VALUE_LEFT_DIRECTION_POS_X);
    Position projectile_position(adjusted_pos_x, duck_position.pos_y);
    Projectile projectile(ProjectileType::CowboyBullet, projectile_position, directions, MAX_DISTANCE, VELOCITY);
    std::vector<Projectile> projectiles;
    projectiles.push_back(projectile);
    need_reload = true;
    block_shoot = true;
    time_to_reaload = TIME_TO_REALOAD;
    std::pair<std::vector<Projectile>, Position> result(projectiles, duck_position);
    return std::optional<std::pair<std::vector<Projectile>, Position>>(result);
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