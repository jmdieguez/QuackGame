#include "duck.h"

#define X_VELOCITY 4

Duck::Duck(const uint8_t &i, const uint16_t &initial_x, const uint16_t &initial_y) : id(i), position(initial_x, initial_y) {}
    
Duck::~Duck() {}

void Duck::pickup_gun(std::shared_ptr<Gun> &gun_ptr) { gun = gun_ptr; }

void Duck::drop_gun() { gun = nullptr; }

void Duck::shoot() { shooting = true; }

void Duck::flap() { 
    action = DuckAction::FLAPPING;
    shooting = false;
}

void Duck::jump() { action = DuckAction::JUMPING; }

void Duck::lay() { action = DuckAction::LAYING; }

void Duck::step() {
    if (action == DuckAction::MOVING) {
        if (looking_right) {
            position.move_x(X_VELOCITY);
        } else {
            position.move_x(-X_VELOCITY);
        }
    } 
    
    if (action == DuckAction::SHOOTING && gun != nullptr) {
        ShootEvent shoot_event = gun->shoot(looking_right, looking_up);
    }
}

// true if duck dies after receiving the shot
bool Duck::receive_shot() { 
    if (has_chestplate) {
        has_chestplate = false;
        return false;
    } else if (has_helmet) {
        has_helmet = false;
        return false;
    } else {
        return true;
    }
}

DuckSnapshot Duck::get_status() {
    PositionSnapshot position_snapshot = position.get_status();
    GunSnapshot gun_snapshot = gun->get_status();
    return DuckSnapshot(id,
                        position_snapshot,
                        action,
                        shooting,
                        looking_right,
                        looking_up,
                        has_chestplate,
                        has_helmet,
                        is_alive,
                        gun_snapshot);
}