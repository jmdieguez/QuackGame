#ifndef SERVER_DUCK_H
#define SERVER_DUCK_H

#include <functional>
#include <memory>
#include <utility>

#include "../../common/duck_actions.h"
#include "../../common/position.h"
#include "../../common/snapshots.h"
#include "gun.h"

class Duck {
private:
    const uint8_t id;
    Position position;
    DuckAction action = DuckAction::IDLE;
    bool shooting = false;
    bool looking_right = true;
    bool looking_up = false;
    bool has_chestplate = false;
    bool has_helmet = false;
    bool is_alive = true;
    std::shared_ptr<Gun> gun; // Para polimorfismo
public:
    Duck(const uint8_t &i, const uint16_t &initial_x, const uint16_t &initial_y);
    ~Duck();

    // Actions
    void pickup_gun(std::shared_ptr<Gun> &gun_ptr);
    void drop_gun();
    void shoot();
    void flap();
    void lay();
    void jump();
    bool receive_shot(); // true if duck dies after receiving the shot

    // Get current duck snapshot
    DuckSnapshot get_status();

    // Simulate an iteration
    void step();
};

#endif // SERVER_DUCK_H
