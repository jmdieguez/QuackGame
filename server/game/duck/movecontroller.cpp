#include "movecontroller.h"
#include "defs.h"

MoveController::MoveController() {}

bool MoveController::validate_position(const Map &map, const Size &size, const Position &position)
{
    Position end_hitbox(position.x + size.width - 1, position.y + size.height - 1);
    return map.validate_coordinate(position) && map.validate_coordinate(end_hitbox);
}

void MoveController::move_horizontal(Position &position, Size &size, DuckStatus &status, Map &map)
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
        if (validate_position(map, size, new_position))
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

void MoveController::collision_detector(Position &position, Size &size, DuckStatus &status, Map &map)
{
    Position below_left(position.x, position.y + size.height);
    Position below_right(position.x + size.width - 1, position.y + size.height - 1);
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
        y_velocity = Y_VELOCITY_FLAPPING;
        status.flapping = false;
        return;
    }
    status.flapping = false;
    y_velocity -= Y_VELOCITY_FALL;
}

void MoveController::move_vertical(Position &position, Size &size, Map &map, int &y_velocity)
{
    std::cout << "Me muevo verticalmente" << std::endl;

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
        std::cout << "La nueva posicion en y es: " << (int)new_position.y << std::endl;
        if (validate_position(map, size, new_position))
        {
            position = new_position;
            i++;
        }
        else
        {
            std::cout << "La nueva posicion fallada en y es: " << (int)new_position.y << std::endl;
            y_velocity = Y_VELOCITY_INITIAL;
            break;
        }
    }
}

void MoveController::move_bent_down(DuckStatus &status, Position &position, Size &size, Map &map)
{
    int w = DUCK_BENT_DOWN_WIDTH, h = DUCK_BENT_DOWN_HEIGHT;
    if (!status.bent_down || size.height == h || size.width == w)
        return;
    int diff_w = DUCK_BENT_DOWN_WIDTH - DUCK_DEFAULT_WIDTH;
    int diff_h = DUCK_DEFAULT_HEIGHT - DUCK_BENT_DOWN_HEIGHT;
    Size new_size_bent_down(w, h);
    Position new_position_bent_down(position.x - diff_w, position.y + diff_h);

    int i = 1;
    while (i <= diff_w)
    {
        Position new_position(position.x - i, position.y);
        Position end_hitbox(new_position.x + w - 1, new_position.y + h - 1);
        if (map.validate_coordinate(new_position) && map.validate_coordinate(end_hitbox))

            i++;
        else
        {
            status.bent_down = false;
            return;
        }
    }
    i = 1;
    while (i <= diff_h)
    {
        Position new_position(position.x, position.y + i);
        Position end_hitbox(new_position.x + w - 1, new_position.y + h - 1);
        if (map.validate_coordinate(new_position) && map.validate_coordinate(end_hitbox))
            i++;
        else
        {
            status.bent_down = false;
            return;
        }
    }
    size = new_size_bent_down;
    position = new_position_bent_down;
}

void MoveController::remove_bent_down(DuckStatus &status, Position &position, Size &size)
{
    int w = DUCK_DEFAULT_WIDTH, h = DUCK_DEFAULT_HEIGHT;
    if (status.bent_down || size.height == h || size.width == w)
        return;
    int diff_w = DUCK_BENT_DOWN_WIDTH - DUCK_DEFAULT_WIDTH;
    int diff_h = DUCK_DEFAULT_HEIGHT - DUCK_BENT_DOWN_HEIGHT;
    Size new_size_bent_down(w, h);
    Position new_position_bent_down(position.x + diff_w, position.y - diff_h);
    size = new_size_bent_down;
    position = new_position_bent_down;
}

MoveController::~MoveController() {}