
#include "projectilegrenade.h"

#define TIME_FIRE 10
#define TIME_TO_EXPLOSION 10

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

ProjectileGrenade::ProjectileGrenade(const Position &p, const std::pair<int, int> &d, uint8_t velocity) : Projectile(ProjectileType::Grenade, TextureFigure::GrenadeFigure, p, d, velocity),
                                                                                                          dispersion(std::make_shared<DispersionGrenade>()),
                                                                                                          time_to_explosion(TIME_TO_EXPLOSION), time_fire(TIME_FIRE),
                                                                                                          trayectory(0), change_direction(false) {}

void ProjectileGrenade::move()
{

    std::cout << "Puedo mover" << std::endl;
    if (dispersion != nullptr)
    {
        if (direction.first != 0)
        {
            std::cout << "Lo muevo en x" << std::endl;
            position.x += direction.first * velocity;
            std::cout << "Lo muevo en y" << std::endl;
            position.y += dispersion->calculate_dispersion(trayectory);
        }
        if (direction.second == -1)
        {
            position.y += direction.second * velocity;
            position.x += dispersion->calculate_dispersion(trayectory);
        }
    }
    else
    {
        position.x += direction.first * velocity;
        position.y += direction.second * velocity;
    }
    trayectory++;
}

void ProjectileGrenade::cancel_move()
{
    position.x -= direction.first * velocity;
    position.y -= direction.second * velocity;
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
