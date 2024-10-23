#ifndef SERVER_DUCK_H
#define SERVER_DUCK_H

#include <memory>

#include "../../common/duck_dto.h"
#include "gun.h"

class Duck {
private:
    std::pair<uint16_t, uint16_t> position;
    std::pair<uint8_t, uint8_t> direction;
    bool has_chestplate;
    bool has_helmet;
    bool is_alive;
    std::shared_ptr<Gun> gun; // Para polimorfismo
public:
    Duck(std::pair<uint16_t, uint16_t> &p) : position(p), has_chestplate(false), has_helmet(false), is_alive(true) {}
    
    ~Duck() {}

    void pickup_gun(std::shared_ptr<Gun> &gun_ptr) {
        gun = gun_ptr;
    }

    void drop_gun() {
        gun = nullptr;
    }

    DuckDTO get_status() {
        return DuckDTO(position, direction, has_chestplate, has_helmet, is_alive, gun->get_status());
    }
};

#endif // SERVER_DUCK_H
