#include "duck.h"
#include <optional>

#define DUCK_HITBOX_X 16
#define DUCK_HITBOX_Y 24

#define DUCK_WIDTH 32
#define DUCK_HEIGHT 32

Duck::Duck(const uint8_t &i, const Position &p) : Hitbox(p, Size(DUCK_WIDTH, DUCK_HEIGHT)), id(i),
                                                  y_velocity(Y_VELOCITY_INITIAL)
{
}

Duck::~Duck() {}

void Duck::move(Direction direction)
{
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

void Duck::drop_gun(Map &map)
{
    GunController::drop_gun(map, position, size, status);
}

void Duck::drop_gun(std::vector<std::shared_ptr<Projectile>> &projectiles)
{
    (void)projectiles;
    // TODO usar para la granada
}

void Duck::shoot()
{
    if (gun == nullptr)
        return;
    status.shooting = true;
}

void Duck::stop_shooting()
{
    GunController::stop_shooting(status);
}

void Duck::jump()
{
    if (status.grounded)
    {
        status.jumping = true;
        return;
    }
    status.flapping = true;
}

void Duck::stand_up()
{
    status.bent_down = false;
}

void Duck::grab(Map &map)
{
    GunController::grab(map, [this](const Hitbox &a)
                        { return intersects(a); });
}

void Duck::lay()
{
    status.bent_down = true;
}

void Duck::step(Map &map, std::vector<std::shared_ptr<Projectile>> &projectiles, std::vector<SoundType> &sounds)
{
    if (status.mooving)
    {
        std::function<int(int, int)> operation = status.looking_right ? [](int a, int b)
        { return a + b; }                                             : // if looking right, increment x
                                                     [](int a, int b)
        { return a - b; }; // if looking, decrease x
        int i = 1;
        while (i <= X_VELOCITY)
        {
            Position new_position(operation(position.x, 1), position.y);
            Position end_hitbox(new_position.x + DUCK_HITBOX_X - 1, new_position.y + DUCK_HITBOX_Y - 1);
            if (map.validate_coordinate(new_position) && map.validate_coordinate(end_hitbox))
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

    Position below_left(position.x, position.y + DUCK_HITBOX_Y);
    Position below_right(position.x + DUCK_HITBOX_X - 1, position.y + DUCK_HITBOX_Y);
    status.grounded = map.has_something_in(below_left) || map.has_something_in(below_right);
    status.falling = false;
    if (status.grounded)
    {
        if (status.jumping)
        {
            y_velocity = Y_VELOCITY_ON_JUMP; // take a big impulse at the start
            status.jumping = false;
            status.falling = false;
            status.start_jumping = true;
        }
        else
        {
            y_velocity = Y_VELOCITY_INITIAL;
            status.start_jumping = false;
        }
    }
    else
    {
        if (y_velocity < 0)
            status.falling = true;

        if (status.flapping && y_velocity < 0)
        {
            y_velocity = -2;
            status.flapping = false;
            return;
        }
        status.flapping = false;
        y_velocity -= 1;
    }

    if (y_velocity != Y_VELOCITY_INITIAL)
    {
        std::function<int(int, int)> operation = (y_velocity < Y_VELOCITY_INITIAL) ? [](int a, int b)
        { return a + b; }                                                          : // if falling, increment y
                                                     [](int a, int b)
        { return a - b; }; // if elevating, decrease y
        int i = 1;
        int abs_y_velocity = std::abs(y_velocity);
        while (i <= abs_y_velocity)
        {
            Position new_position(position.x, operation(position.y, 1));
            Position end_hitbox(new_position.x + DUCK_HITBOX_X - 1, new_position.y + DUCK_HITBOX_Y - 1); // El duck ocupa 18x24
            if (map.validate_coordinate(new_position) && map.validate_coordinate(end_hitbox))
            {
                position = new_position;
                i++;
            }
            else
            {
                y_velocity = Y_VELOCITY_INITIAL;
                break;
            }
        }
    }

    if (status.shooting && !block_shooting_command && gun != nullptr)
        GunController::shoot(status, position, map, projectiles, sounds);
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

DuckSnapshot Duck::get_status()
{
    GunType gun_type = get_gun_type();
    TextureFigure gun_texture = get_gun_texture();
    Size gun_size = get_gun_size();
    Position aux(position.x - 8, position.y - 8);
    Position gun_position = get_gun_position(position, size, status);
    Position aux_gun(gun_position.x - 8, gun_position.y - 8);
    uint16_t gun_angle = get_gun_angle(status);
    return DuckSnapshot(id,
                        aux,
                        size, gun_type, gun_texture, gun_size, gun_position, gun_angle, status);
    //  100,
    //  status,
    // gun_snapshot);
}