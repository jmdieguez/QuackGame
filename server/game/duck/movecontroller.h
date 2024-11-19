#include <functional>
#include "../map.h"
#include "../../../common/duck.h"
#include "../../../common/position.h"

#define X_VELOCITY 4
#define Y_VELOCITY_INITIAL 0
#define Y_VELOCITY_ON_JUMP 16

#define DUCK_HITBOX_X 16
#define DUCK_HITBOX_Y 24

class MoveController
{
private:
public:
    MoveController() {};
    void move_horizontal(Position &position, DuckStatus &status, Map &map)
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
    };
    ~MoveController() {};
};
