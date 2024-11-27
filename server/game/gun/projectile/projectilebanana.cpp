#include "projectilebanana.h"

#define VELOCITY_X 3
#define VELOCITY_Y 3
#define MAX_TRAYECTORY 32 * 2

#define GUN_WIDTH 15
#define GUN_HEIGHT 15

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

ProjectileBanana::ProjectileBanana(DuckStatus &status, const Position &duck_position) : Projectile(ProjectileType::Banana, TextureFigure::None, VELOCITY_X),
                                                                                        status(status),
                                                                                        duck_position(duck_position),
                                                                                        trayectory(0), is_throwing(false), collide_wall(false)
{
}

void ProjectileBanana::move(const std::function<bool(Position &)> &validator)
{

    if (collide_wall)
    {

        int i = 1;
        while (i <= VELOCITY_Y)
        {
            Position new_position(position.x, position.y + 1);
            Position end_hitbox(new_position.x + size.width - 1, new_position.y + size.height - 1);
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
            Position end_hitbox(new_position.x + size.width - 1, new_position.y + size.height - 1);
            if (validator(new_position) && validator(end_hitbox))
            {
                position = new_position;
                i++;
            }
            else
            {
                texture = TextureFigure::BananaThrown;
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
            Position end_hitbox(new_position.x + size.width - 1, new_position.y + size.height - 1);
            if (validator(new_position) && validator(end_hitbox))
            {
                position = new_position;
                i++;
            }
            else
            {
                collide_wall = true;
                texture = TextureFigure::BananaThrown;
                break;
            }
        }
        trayectory += VELOCITY_X;
    }
}

void ProjectileBanana::throw_banana(bool &looking_right)
{
    is_throwing = true;
    texture = TextureFigure::BananaFigure;
    size.width = GUN_WIDTH;
    size.height = GUN_HEIGHT;
    direction = looking_right ? std::make_pair(1, 0) : std::make_pair(-1, 0);
    Position new_position(duck_position.x - 10, duck_position.y - 10);
    position = new_position;
}

void ProjectileBanana::check_collision(Hitbox duck, DuckStatus &status)
{
    if (!intersects(duck))
        return;
    if (texture != TextureFigure::BananaThrown)
        return;
    status.banana_move = true;
    finish = true;
}

ProjectileBanana::~ProjectileBanana()
{
}
