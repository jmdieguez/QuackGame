#ifndef SERVER_DUCK_H
#define SERVER_DUCK_H

#include <functional>
#include <memory>
#include <utility>

#include "../../common/duck_dto.h"
#include "gun.h"

enum class DuckAction {
    IDLE = 0,
    MOVING,
    SHOOTING,
    FLAPPING,
    LAYING,
    JUMPING
};

class Duck {
private:
    std::pair<uint16_t, uint16_t> position;
    DuckAction action = DuckAction::IDLE;
    bool looking_right = true;
    bool looking_up = false;
    bool has_chestplate = false;
    bool has_helmet = false;
    bool is_alive = true;
    std::shared_ptr<Gun> gun; // Para polimorfismo
public:
    Duck(std::pair<uint16_t, uint16_t> &p) : position(p) {}
    ~Duck() {}

    // Actions
    void pickup_gun(std::shared_ptr<Gun> &gun_ptr);
    void drop_gun();
    void shoot();
    void flap();
    void lay();
    void jump();
    bool receive_shot(); // true if duck dies after receiving the shot

    // Duck Snapshot
    DuckDTO get_status();

    // Simulate an iteration
    void step();
};

#endif // SERVER_DUCK_H
