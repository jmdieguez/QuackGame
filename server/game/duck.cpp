#include "duck.h"
#include <optional>

#define DUCK_WIDTH 32
#define DUCK_HEIGHT 32

Duck::Duck(const uint8_t &i, const uint16_t &initial_x, const uint16_t &initial_y) : id(i), position(initial_x, initial_y),
                                                                                     action(DuckAction::IDLE), size(DUCK_WIDTH, DUCK_HEIGHT),
                                                                                     gun(nullptr), block_shooting_command(false) {}

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

void Duck::look_up()
{
    status.looking_up = true;
}

void Duck::stop_looking_up()
{
    status.looking_up = false;
}

GunType Duck::get_gun_type()
{
    return gun == nullptr ? GunType::None : gun.get()->get_type();
}

uint16_t Duck::get_gun_angle() const
{
    return gun == nullptr ? 0 : gun->get_angle(status.looking_right, status.looking_up);
}

Size Duck::get_gun_size() const
{
    return gun == nullptr ? Size(0, 0) : gun->get_size();
}

Position Duck::get_gun_position() const
{
    return gun == nullptr ? Position(0, 0) : gun->get_position_in_duck(size.height, position, status.looking_right, status.looking_up);
}

void Duck::stop_moving() { action = DuckAction::IDLE; }

void Duck::drop_gun()
{
    stop_shooting();
    gun = nullptr;
}

void Duck::drop_gun(std::vector<std::shared_ptr<Projectile>> &projectiles)
{
    Grenade *grenade = (Grenade *)gun.get();
    std::shared_ptr<Projectile> projectil = grenade->get_projectile(status.looking_right, status.looking_up);
    if (projectil == nullptr)
        return;
    projectiles.push_back(grenade->get_projectile(status.looking_right, status.looking_up));
    gun = nullptr;
}

void Duck::shoot() { status.shooting = true; }

void Duck::stop_shooting()
{
    status.shooting = false;
    block_shooting_command = false;
    if (gun->get_type() == GunType::Shotgun)
        ((Shotgun *)gun.get())->check_reset();
    if (gun->get_type() == GunType::Sniper)
        ((Sniper *)gun.get())->check_reset();
    if (gun->get_type() == GunType::AK)
        ((AK *)gun.get())->check_reset();
}

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
        return;
    }
    status.flapping = true;
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

void Duck::step(Map &map, std::vector<std::shared_ptr<Projectile>> &projectiles)
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
            Position new_position(operation(position.x, 1), position.y);
            Position end_hitbox(new_position.x + TILE_SIZE - 1, new_position.y + TILE_SIZE - 1);
            if (map.validate_coordinate(new_position) && map.validate_coordinate(end_hitbox))
            {
                for (auto &[id, gun] : map.get_guns())
                {
                    if (gun.get()->can_take_this_gun(new_position))
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

    Position below_left(position.x, position.y + TILE_SIZE);
    Position below_right(position.x + TILE_SIZE - 1, position.y + TILE_SIZE);
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
            Position end_hitbox(new_position.x + TILE_SIZE - 1, new_position.y + TILE_SIZE - 1); // El duck ocupa 32x32
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
    {

        auto result = gun->shoot(status.looking_right, status.looking_up, position);
        if (!result.has_value() && gun->get_type() == GunType::Shotgun && (((Shotgun *)gun.get())->is_block_shoot()))
        {
            block_shooting_command = true;
            return;
        }
        if (!result.has_value() && gun->get_type() == GunType::Sniper && (((Sniper *)gun.get())->is_block_shoot()))
        {
            block_shooting_command = true;
            return;
        }
        if (!result.has_value())
            return;
        std::vector<std::shared_ptr<Projectile>> shot_projectile = result.value().first;
        Position duck_position_after_shoot = result.value().second;
        if (duck_position_after_shoot.x != position.x || duck_position_after_shoot.y != position.y)
        {
            if (duck_position_after_shoot.x != position.x)
            {
                int start_x = std::min(position.x, duck_position_after_shoot.x);
                int end_x = std::max(position.x, duck_position_after_shoot.x);
                for (int x = status.looking_right ? end_x : start_x;
                     status.looking_right ? x >= start_x : x <= end_x;
                     status.looking_right ? --x : ++x)
                {
                    {
                        Position new_position(x, position.y);
                        if (map.validate_coordinate(new_position))
                        {
                            position.x = (uint16_t)x;
                            continue;
                        }
                        break;
                    }
                }
                if (duck_position_after_shoot.y != position.y)
                {
                    int start_y = std::min(position.y, duck_position_after_shoot.y);
                    int end_y = std::max(position.y, duck_position_after_shoot.y);
                    for (int y = start_y; y <= end_y; ++y)
                    {
                        Position new_position(position.x, y);
                        if (map.validate_coordinate(new_position))
                        {
                            position.y = y;
                            continue;
                        }

                        break;
                    }
                }
            }
        }
        for (std::shared_ptr<Projectile> p : shot_projectile)
            projectiles.push_back(p);
        if (gun->get_type() == GunType::Shotgun && !(((Shotgun *)gun.get())->is_block_shoot()))
            return;
        if (gun->get_type() == GunType::Sniper && !(((Sniper *)gun.get())->is_block_shoot()))
            return;
        if (gun->get_type() == GunType::AK)
            return;
        block_shooting_command = true;
    }
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

bool Duck::is_in_range(Position &position_item)
{
    uint16_t half_tile_size = TILE_SIZE / 2;
    return position_item.x >= position.x && position_item.x < position.x + half_tile_size &&
           position_item.y >= position.y && position_item.y < position.y + TILE_SIZE;
}

DuckSnapshot Duck::get_status()
{
    GunType gun_type = get_gun_type();
    Size gun_size = get_gun_size();
    Position gun_position = get_gun_position();
    uint16_t gun_angle = get_gun_angle();
    return DuckSnapshot(id,
                        position,
                        action, size, gun_type, gun_size, gun_position, gun_angle, status);
    //  100,
    //  status,
    // gun_snapshot);
}