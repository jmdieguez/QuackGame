
#include "projectilegrenade.h"

#define TIME_FIRE 10
#define TIME_TO_EXPLOSION 10

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

ProjectileGrenade::ProjectileGrenade(const ProjectileType &t, const Position &p, const std::pair<int, int> &d, uint8_t velocity) : Projectile(t, p, d, velocity),
                                                                                                                                   time_to_explosion(TIME_TO_EXPLOSION),
                                                                                                                                   time_fire(TIME_FIRE), change_direction(false) {}

void ProjectileGrenade::move()
{
    if (!time_to_explosion)
        return;
    position.pos_x += direction.first * velocity;
    position.pos_y += direction.second * velocity;
    time_to_explosion--;
}

void ProjectileGrenade::cancel_move()
{
    position.pos_x -= direction.first * velocity;
    position.pos_y -= direction.second * velocity;
}

void ProjectileGrenade::collide_walls()
{
    direction.first = 0;
    direction.second = -1;
    change_direction = true;
}

void ProjectileGrenade::reduce_time()
{
    time_to_explosion--;
}

bool ProjectileGrenade::is_change_direction_apply() const
{
    return change_direction;
}
uint8_t ProjectileGrenade::get_time_fire() const
{
    return time_fire;
}

ProjectileGrenade::~ProjectileGrenade()
{
}
