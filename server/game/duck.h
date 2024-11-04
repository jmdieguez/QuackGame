#ifndef SERVER_DUCK_H
#define SERVER_DUCK_H

#define X_VELOCITY 4
#define Y_VELOCITY_INITIAL 0
#define Y_VELOCITY_ON_JUMP 16

#include <functional>
#include <memory>
#include <utility>

#include "../../common/duck.h"
#include "../../common/position.h"
#include "../../common/direction.h"
#include "../../common/snapshots.h"
#include "gun/gun.h"
#include "map.h"

class Duck
{
private:
    uint8_t id;
    Position position;
    DuckStatus status;
    DuckAction action = DuckAction::IDLE;
    std::shared_ptr<Gun> gun;
    int y_velocity = 0;

public:
    explicit Duck(const uint8_t &i, const uint16_t &initial_x, const uint16_t &initial_y);
    ~Duck();

    // Actions
    void move(Direction d);
    void stop_moving();
    void look_up();
    void stop_looking_up();
    void pickup_gun(std::shared_ptr<Gun> &gun_ptr);
    void drop_gun();
    void shoot();
    void stop_shooting();
    void flap();
    void lay();
    void jump();
    bool receive_shot(); // true if duck dies after receiving the shot

    // Get current duck snapshot
    DuckSnapshot get_status();

    // Simulate an iteration
    void step(Map &map, std::map<uint8_t, std::shared_ptr<Gun>> &guns);
};

#endif // SERVER_DUCK_H
