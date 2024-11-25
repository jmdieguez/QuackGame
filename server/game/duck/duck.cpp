#include "duck.h"
#include <optional>

#define X_VELOCITY 4
#define Y_VELOCITY_INITIAL 0
#define Y_VELOCITY_ON_JUMP 16

#define DUCK_WIDTH 15
#define DUCK_HEIGHT 24

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

void Duck::process_movement(Map &map)
{
    if (status.mooving || status.banana_move)
        move_horizontal(position, status, map);

    collision_detector(position, status, map);
    status.grounded ? update_jump_status(status, y_velocity)
                    : update_in_the_air_status(status, y_velocity);

    if (y_velocity != Y_VELOCITY_INITIAL || status.banana_move)
        move_vertical(position, map, y_velocity);
}

void Duck::process_shooting(Map &map, std::vector<std::shared_ptr<Projectile>> &projectiles, std::vector<SoundType> &sounds)
{
    if (!status.shooting && !block_shooting_command && gun != nullptr)
        finish_shooting();

    if (status.gun_grab)
        pick_up(map, status, [this](const Hitbox &a)
                { return intersects(a); });

    if (status.gun_drop)
        gun->get_type() == GunType::Grenade || gun->get_type() == GunType::Banana ? (gun->get_type() == GunType::Grenade ? drop_grenade(status, projectiles) : drop_banana(status, projectiles)) : discard_gun(map, position, size, status);

    if (status.shooting && !block_shooting_command && gun != nullptr)
        fire(status, position, map, projectiles, sounds);
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Duck::Duck(const uint8_t &i, const Position &p, const Color &color) : Hitbox(p, Size(DUCK_WIDTH, DUCK_HEIGHT)), id(i), color(color),
                                                                      y_velocity(Y_VELOCITY_INITIAL)
{
}

Duck::~Duck() {}

void Duck::move(Direction direction)
{
    if (status.banana_move)
        return;
    switch (direction)
    {
    case Direction::RIGHT:
        status.mooving = true;
        status.looking_right = true;
        break;
    case Direction::LEFT:
        status.mooving = true;
        status.looking_right = false;
        break;
    default:
        break;
    }
}

void Duck::stop_moving()
{
    status.mooving = false;
}

void Duck::look_up()
{
    status.looking_up = true;
}

void Duck::stop_looking_up()
{
    status.looking_up = false;
}

void Duck::drop_gun()
{
    if (!gun || status.banana_move)
        return;
    status.gun_drop = true;
}

void Duck::shoot()
{
    if (gun == nullptr || status.bent_down || status.banana_move)
        return;
    status.shooting = true;
}

void Duck::stop_shooting()
{
    if (gun == nullptr || status.banana_move)
        return;
    status.shooting = false;
    block_shooting_command = false;
}

void Duck::jump()
{
    if (status.bent_down || status.banana_move)
        return;
    status.grounded ? status.jumping = true : status.flapping = true;
}

void Duck::stand_up()
{
    status.bent_down = false;
}

void Duck::grab()
{
    if (gun != nullptr || status.banana_move)
        return;
    status.gun_grab = true;
}

void Duck::lay()
{
    if (status.jumping || status.flapping || !status.grounded || status.banana_move)
        return;
    status.bent_down = true;
}

void Duck::step(Map &map, std::vector<std::shared_ptr<Projectile>> &projectiles, std::vector<SoundType> &sounds)
{
    process_movement(map);
    process_shooting(map, projectiles, sounds);
}
// true if duck dies after receiving the shot
void Duck::set_receive_shot()
{
    if (status.has_chestplate)
        status.has_chestplate = false;
    else if (status.has_helmet)
        status.has_helmet = false;
    else
        status.is_alive = false;
}

bool Duck::is_alive() const
{
    return status.is_alive;
}

DuckStatus &Duck::get_duck_status()
{
    return status;
}

DuckSnapshot Duck::get_status()
{
    GunType gun_type = get_gun_type();
    TextureFigure gun_texture = get_gun_texture();
    Size gun_size = get_gun_size();
    Position gun_position = get_gun_position(position, size, status);
    uint16_t gun_angle = get_gun_angle(status);
    return DuckSnapshot(id,
                        position,
                        size, gun_type, gun_texture, gun_size, gun_position, gun_angle, status, color);
}