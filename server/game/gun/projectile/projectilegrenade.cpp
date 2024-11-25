
#include "projectilegrenade.h"

#define TIME_TO_EXPLOSION 100
#define VELOCITY_X 3
#define VELOCITY_Y 3
#define MAX_TRAYECTORY 32 * 2

#define GUN_WIDTH 15
#define GUN_HEIGHT 15

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

void ProjectileGrenade::set_value_explosion()
{
    texture = TextureFigure::None;
    direction = std::make_pair(1, 0);
    Position new_position(duck_position.x - 10, duck_position.y - 10);
    position = new_position;
}

ProjectileGrenade::ProjectileGrenade(DuckStatus &status, const Position &duck_position) : Projectile(ProjectileType::Grenade, TextureFigure::None, VELOCITY_X),
                                                                                          status(status),
                                                                                          duck_position(duck_position),
                                                                                          time_to_explosion(TIME_TO_EXPLOSION),
                                                                                          trayectory(0), is_throwing(false), collide_wall(false)

{
}

void ProjectileGrenade::move(const std::function<bool(Position &)> &validator)
{

    time_to_explosion--;
    if (!time_to_explosion)
    {
        if (!is_throwing)
        {
            status.is_alive = false;
            set_value_explosion();
        }
        finish = true;
        return;
    }

    if (!is_throwing)
        return;
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
            Position end_hitbox(new_position.x + 15 - 1, new_position.y + 15 - 1);
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
            Position end_hitbox(new_position.x + 15 - 1, new_position.y + 15 - 1);
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
}

void ProjectileGrenade::throw_grenade(bool &looking_right)
{
    is_throwing = true;
    texture = TextureFigure::GrenadeFigure;
    size.width = GUN_WIDTH;
    size.height = GUN_HEIGHT;
    direction = looking_right ? std::make_pair(1, 0) : std::make_pair(-1, 0);
    Position new_position(duck_position.x - 10, duck_position.y - 10);
    position = new_position;
}

ProjectileGrenade::~ProjectileGrenade()
{
}
