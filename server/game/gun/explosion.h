#include "../../../common/position.h"

class Explosion
{
private:
    Position position;

public:
    explicit Explosion(Position position) : position(position) {};
    ~Explosion() {};
};
