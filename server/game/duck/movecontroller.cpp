#include "movecontroller.h"

MoveController::MoveController() {}

void MoveController::move_horizontal(Position &position, DuckStatus &status, Map &map)
{
    std::function<int(int, int)> operation = status.looking_right
                                                 ? [](int a, int b)
    { return a + b; }
                                                 : [](int a, int b)
    { return a - b; };

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
            status.banana_move = false;
            break;
        }
    }
}

void MoveController::collision_detector(Position &position, DuckStatus &status, Map &map)
{
    Position below_left(position.x, position.y + DUCK_HITBOX_Y);
    Position below_right(position.x + DUCK_HITBOX_X - 1, position.y + DUCK_HITBOX_Y);
    status.grounded = map.has_something_in(below_left) || map.has_something_in(below_right);
    status.falling = false;
}

void MoveController::update_jump_status(DuckStatus &status, int &y_velocity)
{
    if (status.jumping)
    {
        y_velocity = Y_VELOCITY_ON_JUMP;
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

void MoveController::update_in_the_air_status(DuckStatus &status, int &y_velocity)
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

void MoveController::move_vertical(Position &position, Map &map, int &y_velocity)
{
    std::function<int(int, int)> operation = (y_velocity < Y_VELOCITY_INITIAL)
                                                 ? [](int a, int b)
    { return a + b; }
                                                 : [](int a, int b)
    { return a - b; };

    int i = 1;
    int abs_y_velocity = std::abs(y_velocity);
    while (i <= abs_y_velocity)
    {
        Position new_position(position.x, operation(position.y, 1));
        Position end_hitbox(new_position.x + DUCK_HITBOX_X - 1, new_position.y + DUCK_HITBOX_Y - 1);
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

MoveController::~MoveController() {}