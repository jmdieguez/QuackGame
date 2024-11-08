#include "duck.h"
#include <optional>

Duck::Duck(const uint8_t &i, const uint16_t &initial_x, const uint16_t &initial_y) : id(i), position(initial_x, initial_y), gun(nullptr) {}

Duck::~Duck() {}

void Duck::move(Direction direction)
{
    switch (direction)
    {
    case Direction::RIGHT:
        action = DuckAction::MOVING;
        status.looking_right = true;
        break;
    case Direction::LEFT:
        action = DuckAction::MOVING;
        status.looking_right = false;
        break;
    default:
        action = DuckAction::IDLE;
        break;
    }
}

void Duck::look_up() { status.looking_up = true; }

void Duck::stop_looking_up() { status.looking_up = false; }

GunType Duck::get_gun_type()
{
    return gun == nullptr ? GunType::None : gun.get()->get_type();
}

void Duck::stop_moving() { action = DuckAction::IDLE; }

void Duck::drop_gun()
{
    stop_shooting();
    gun = nullptr;
}

void Duck::shoot() { status.shooting = true; }

void Duck::stop_shooting() { status.shooting = false; }

void Duck::flap()
{
    action = DuckAction::FLAPPING;
    status.shooting = false;
}

void Duck::jump()
{
    if (status.grounded)
    {
        action = DuckAction::JUMPING;
        status.jumping = true;
    }
}

void Duck::stand_up()
{
    status.bent_down = false;
    action = DuckAction::IDLE;
}

void Duck::lay()
{
    status.bent_down = true;
    action = DuckAction::LAYING;
}

void Duck::step(Map &map, std::vector<Projectile> &projectiles)
{
    if (action == DuckAction::MOVING)
    {
        std::function<int(int, int)> operation = status.looking_right ? [](int a, int b)
        { return a + b; }                                             : // if looking right, increment x
                                                     [](int a, int b)
        { return a - b; }; // if looking, decrease x
        std::optional<uint16_t> gun_id_to_erase;
        int i = 1;
        while (i <= X_VELOCITY)
        {
            Position new_position(operation(position.pos_x, 1), position.pos_y);
            Position end_hitbox(new_position.pos_x + TILE_SIZE - 1, new_position.pos_y + TILE_SIZE - 1);
            if (map.validate_coordinate(new_position) && map.validate_coordinate(end_hitbox))
            {
                for (auto &[id, gun] : map.get_guns())
                {
                    if (gun.get()->can_take_this_gun(new_position.pos_x, new_position.pos_y))
                    {
                        this->gun = gun;
                        gun_id_to_erase = id;
                        break;
                    }
                }
                if (gun_id_to_erase.has_value())
                    map.remove_gun(gun_id_to_erase.value());
                position = new_position;
                i++;
            }
            else
            {
                break;
            }
        }
    }

    Position below_left(position.pos_x, position.pos_y + TILE_SIZE);
    Position below_right(position.pos_x + TILE_SIZE - 1, position.pos_y + TILE_SIZE);
    status.grounded = map.has_something_in(below_left) || map.has_something_in(below_right);

    if (status.grounded)
    {
        if (status.jumping)
        {
            y_velocity = Y_VELOCITY_ON_JUMP; // take a big impulse at the start
            status.jumping = false;
        }
        else
        {
            y_velocity = Y_VELOCITY_INITIAL;
        }
    }
    else
    {
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
            Position new_position(position.pos_x, operation(position.pos_y, 1));
            Position end_hitbox(new_position.pos_x + TILE_SIZE - 1, new_position.pos_y + TILE_SIZE - 1); // El duck ocupa 32x32
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

    if (status.shooting && gun != nullptr && gun->have_ammo())
    {

        Projectile projectile = gun->shoot(status.looking_right, status.looking_up, position);
        projectiles.push_back(projectile);
        status.shooting = false;
    }
}

// true if duck dies after receiving the shot
bool Duck::receive_shot()
{
    if (status.has_chestplate)
    {
        status.has_chestplate = false;
        return false;
    }
    else if (status.has_helmet)
    {
        status.has_helmet = false;
        return false;
    }
    else
    {
        return true;
    }
}

DuckSnapshot Duck::get_status()
{
    PositionSnapshot position_snapshot = position.get_status();
    GunType gun_type = get_gun_type();
    return DuckSnapshot(id,
                        position_snapshot,
                        action, gun_type, status);
    //  100,
    //  status,
    // gun_snapshot);
}