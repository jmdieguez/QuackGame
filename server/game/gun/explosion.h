#include "../../../common/size.h"
#include "../../../common/snapshots.h"
#include "../../../common/position.h"
#include "../../../common/texturefigure.h"

class Explosion
{
private:
    Size size;
    Position position;
    uint8_t time;

public:
    explicit Explosion(const Size &size, const Position &position) : size(size), position(position), time(30) {};
    ExplosionSnapshot get_status()
    {
        return ExplosionSnapshot(size, position, TextureFigure::ExplosionFigure);
    };
    void time_decrement()
    {
        if (!time)
            return;
        time--;
    }

    bool is_finish()
    {
        return !time;
    }
    ~Explosion() {};
};
