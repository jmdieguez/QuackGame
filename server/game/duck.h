#ifndef SERVER_DUCK_H
#define SERVER_DUCK_H

#define X_VELOCITY 4
#define Y_VELOCITY_INITIAL 0
#define Y_VELOCITY_ON_JUMP 16

#include <functional>
#include <memory>
#include <utility>

#include "../../common/duck.h"
#include "../../common/direction.h"
#include "../../common/snapshots.h"
#include "../../common/soundtype.h"
#include "gun/gun.h"
#include "map.h"
#include "hitbox.h"

class Duck : public Hitbox
{
private:
    uint8_t id;
    DuckStatus status;
    std::shared_ptr<Gun> gun;
    int y_velocity;
    bool block_shooting_command;
    uint16_t get_gun_angle() const;
    Size get_gun_size() const;
    Position get_gun_position() const;

public:
    explicit Duck(const uint8_t &i, const Position &p);
    ~Duck();

    // Actions
    void move(Direction d);
    void stop_moving();
    void look_up();
    void stop_looking_up();
    GunType get_gun_type();
    TextureFigure get_gun_texture();
    void drop_gun(Map &map);
    void shoot();
    void stop_shooting();
    void drop_gun(std::vector<std::shared_ptr<Projectile>> &projectiles);
    void lay();
    void jump();
    void stand_up();
    void set_receive_shot();
    void grab(Map &map);

    // Get current duck snapshot
    DuckSnapshot get_status();

    bool is_alive() const {
        return status.is_alive;
    }

    // Simulate an iteration
    void step(Map &map, std::vector<std::shared_ptr<Projectile>> &projectiles, std::vector<SoundType> &sounds);
};

#endif // SERVER_DUCK_H
