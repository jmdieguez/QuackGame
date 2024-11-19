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
    MoveController();
    void move_horizontal(Position &position, DuckStatus &status, Map &map);
    void collision_detector(Position &position, DuckStatus &status, Map &map);
    void update_jump_status(DuckStatus &status, int &y_velocity);
    void update_in_the_air_status(DuckStatus &status, int &y_velocity);
    void move_vertical(Position &position, Map &map, int &y_velocity);
    ~MoveController();
};
