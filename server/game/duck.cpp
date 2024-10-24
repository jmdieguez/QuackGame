#include "duck.h"

#define X_VELOCITY 4

Duck::Duck(const uint8_t &i, const uint16_t &initial_x, const uint16_t &initial_y) : id(i), position(initial_x, initial_y) {}

Duck::~Duck() {}

void Duck::move(Direction &direction)
{
    action = DuckAction::MOVING;
    switch (direction)
    {
    case Direction::RIGHT:
        status.looking_right = true;
        break;
    case Direction::LEFT:
        status.looking_right = false;
        break;
    default:
        action = DuckAction::IDLE;
        break;
    }
}

void Duck::look_up() { status.looking_up = true; }

void Duck::stop_looking_up() { status.looking_up = false; }

void Duck::stop_moving() { action = DuckAction::IDLE; }

void Duck::pickup_gun(std::shared_ptr<Gun> &gun_ptr) { gun = gun_ptr; }

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

void Duck::jump() { action = DuckAction::JUMPING; }

void Duck::lay() { action = DuckAction::LAYING; }

void Duck::step()
{
    if (action == DuckAction::MOVING)
    {
        if (status.looking_right)
        {
            position.move_x(X_VELOCITY);
        }
        else
        {
            position.move_x(-X_VELOCITY);
        }
    }

    if (status.shooting && gun != nullptr)
    {
        ShootEvent shoot_event = gun->shoot(status.looking_right, status.looking_up);
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
    GunSnapshot gun_snapshot = gun->get_status();
    return DuckSnapshot(id, 100,
                        position_snapshot,
                        action,
                        status,
                        gun_snapshot);
}