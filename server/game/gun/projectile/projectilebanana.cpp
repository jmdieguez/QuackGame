#include "projectilebanana.h"

#define VELOCITY_X 3
#define VELOCITY_Y 3
#define MAX_TRAYECTORY 32 * 2

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

ProjectileBanana::ProjectileBanana(const Hitbox &h, const std::pair<int, int> &d) : Projectile(ProjectileType::Banana, TextureFigure::BananaFigure, h, d, VELOCITY_X),
                                                                                    trayectory(0), collide_wall(false)
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
void ProjectileBanana::cancel_move()
{
}

void ProjectileBanana::collide_walls()
{
}

void ProjectileBanana::checkCollision(Hitbox duck, DuckStatus &status)
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
