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
    DuckAction action;
    std::shared_ptr<Gun> gun;
    int y_velocity = 0;
    bool block_shooting_command;
    Size get_gun_size();

public:
    explicit Duck(const uint8_t &i, const uint16_t &initial_x, const uint16_t &initial_y);
    ~Duck();

    // Actions
    void move(Direction d);
    void stop_moving();
    void look_up();
    void stop_looking_up();
    void drop_gun();
    void shoot();
    GunType get_gun_type();
    void stop_shooting();
    void drop_gun(std::vector<std::shared_ptr<Projectile>> &projectiles);
    void flap();
    void lay();
    void jump();
    void stand_up();
    void set_receive_shot();
    bool is_in_range(Position &position_item);

    // Get current duck snapshot
    DuckSnapshot get_status();

    // Simulate an iteration
    void step(Map &map, std::vector<std::shared_ptr<Projectile>> &projectiles);
};

#endif // SERVER_DUCK_H
