#include <functional>
#include "../map.h"
#include "../../../common/duck.h"
#include "../../../common/position.h"

class MoveController
{
private:
    bool validate_position(const Map &map, const Size &size, const Position &position);
public:
    MoveController();
    void move_horizontal(Position &position, Size &size, DuckStatus &status, Map &map);
    void collision_detector(Position &position, Size &size, DuckStatus &status, Map &map);
    void update_jump_status(DuckStatus &status, int &y_velocity);
    void update_in_the_air_status(DuckStatus &status, int &y_velocity);
    void move_vertical(Position &position, Size &size, Map &map, int &y_velocity);
    void move_bent_down(DuckStatus &status, Position &position, Size &size, Map &map);
    void remove_bent_down(DuckStatus &status, Position &position, Size &size);
    ~MoveController();
};
