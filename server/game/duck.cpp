#include "duck.h"

Duck::Duck(std::pair<uint16_t, uint16_t> &p) : position(p) {}
    
Duck::~Duck() {}

#define X_VELOCITY 4

void Duck::pickup_gun(std::shared_ptr<Gun> &gun_ptr) { gun = gun_ptr; }

void Duck::drop_gun() { gun = nullptr; }

void Duck::shoot() { action = DuckAction::SHOOTING; }

void Duck::flap() { action = DuckAction::FLAPPING; }

void Duck::jump() { action = DuckAction::JUMPING; }

void Duck::lay() { action = DuckAction::LAYING; }

void Duck::step() {
    if (action == DuckAction::MOVING) {
        if (looking_right) {
            position = std::pair<uint16_t, uint16_t>(position.first + X_VELOCITY, position.second);
        } else {
            position = std::pair<uint16_t, uint16_t>(position.first - X_VELOCITY, position.second);
        }
    } else if (action == DuckAction::SHOOTING && gun != nullptr) {
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

DuckDTO Duck::get_status() {
    // return DuckDTO(position, looking_right, looking_up, has_chestplate, has_helmet, is_alive, gun->get_status());
}