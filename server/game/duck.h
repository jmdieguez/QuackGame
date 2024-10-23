#ifndef SERVER_DUCK_H
#define SERVER_DUCK_H

#include <functional>
#include <memory>
#include <utility>

#include "../../common/duck.h"
#include "../../common/position.h"
#include "../../common/snapshots.h"
#include "gun.h"

class Duck {
private:
    const uint8_t id;
    Position position;
    DuckStatus status;
    DuckAction action = DuckAction::IDLE;
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
