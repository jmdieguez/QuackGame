
#include "projectilegrenade.h"

#define TIME_TO_EXPLOSION 100
#define VELOCITY_X 3
#define VELOCITY_Y 3
#define MAX_TRAYECTORY 32 * 2

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

ProjectileGrenade::ProjectileGrenade(const Hitbox &h, const std::pair<int, int> &d) : Projectile(ProjectileType::Grenade, TextureFigure::GrenadeFigure, h, d, VELOCITY_X),
                                                                                      time_to_explosion(TIME_TO_EXPLOSION),
                                                                                      trayectory(0), collide_wall(false)
{
}

void ProjectileGrenade::move(const std::function<bool(Position &)> &validator)
{
    if (!time_to_explosion)
    {
        finish = true;
        return;
    }
    if (collide_wall)
    {

        int i = 1;
        while (i <= VELOCITY_Y)
        {
            Position new_position(position.x, position.y + 1);
            Position end_hitbox(new_position.x + 15 - 1, new_position.y + 15 - 1);
            if (validator(new_position) && validator(end_hitbox))
            {
                position = new_position;
                i++;
            }
            else
            {
                break;
            }
        }
    }

    else
    {

        int i = 1;
        while (i <= VELOCITY_X)
        {
            Position new_position(position.x + direction.first, position.y);
            Position end_hitbox(new_position.x + 8 - 1, new_position.y + 8 - 1);
            if (validator(new_position) && validator(end_hitbox))
            {
                position = new_position;
                i++;
            }
            else
            {
                collide_wall = true;
                break;
            }
        }
        if (collide_wall)
            return;
        i = 1;
        while (i <= VELOCITY_Y)
        {
            Position new_position(position.x, position.y + (trayectory < MAX_TRAYECTORY ? -1 : 1));
            Position end_hitbox(new_position.x + 8 - 1, new_position.y + 8 - 1);
            if (validator(new_position) && validator(end_hitbox))
            {
                position = new_position;
                i++;
            }
            else
            {
                collide_wall = true;
                break;
            }
        }
        trayectory += VELOCITY_X;
    }
    time_to_explosion--;
}

ProjectileGrenade::~ProjectileGrenade()
{
}
