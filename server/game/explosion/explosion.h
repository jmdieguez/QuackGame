#
#include <utility>
#include <cstdint>
#include "../../../common/snapshots.h"

class Explosion
{
private:
    uint8_t time_explosion;
    std::pair<int, int> direction;
    bool exploted;
    uint16_t phase_exploted;

public:
    explicit Explosion(std::pair<int, int> direction, uint8_t time_explosion) : direction(direction), time_explosion(time_explosion), exploted(false), phase_exploted(0) {};
    bool is_exploted()
    {
        return exploted;
    }
    void change_exploted()
    {
        exploted = true;
    }
    virtual void move() = 0;
    virtual bool is_finish_explode() = 0;
    virtual bool is_time_to_explode() = 0;
    virtual void collide_wall() = 0;
    virtual void change_state() = 0;
    virtual ~Explosion() {};
};
