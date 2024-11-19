#ifndef SERVER_DUCK_H
#define SERVER_DUCK_H

#define X_VELOCITY 4
#define Y_VELOCITY_INITIAL 0
#define Y_VELOCITY_ON_JUMP 16

#include <functional>
#include <memory>
#include <utility>

#include "movecontroller.h"
#include "guncontroller.h"
#include "../gun/gun.h"
#include "../map.h"
#include "../hitbox.h"
#include "../../../common/duck.h"
#include "../../../common/direction.h"
#include "../../../common/snapshots.h"
#include "../../../common/soundtype.h"

class Duck : public Hitbox, public GunController, public MoveController
{
private:
    uint8_t id;
    DuckStatus status;
    int y_velocity;

public:
    explicit Duck(const uint8_t &i, const Position &p);
    ~Duck();

    // Actions
    void move(Direction d);
    void stop_moving();
    void look_up();
    void stop_looking_up();
    void drop_gun();
    void shoot();
    void stop_shooting();
    void drop_gun(std::vector<std::shared_ptr<Projectile>> &projectiles);
    void lay();
    void jump();
    void stand_up();
    void set_receive_shot();
    void grab();

    // Get current duck snapshot
    DuckSnapshot get_status();

    bool is_alive() const
    {
        return status.is_alive;
    }

    // Simulate an iteration
    void step(Map &map, std::vector<std::shared_ptr<Projectile>> &projectiles, std::vector<SoundType> &sounds);
};

#endif // SERVER_DUCK_H
