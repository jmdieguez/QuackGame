#ifndef SERVER_DUCK_H
#define SERVER_DUCK_H

#include <memory>

#include "gun.h"

class Duck {
private:
    bool has_chestplate;
    bool has_helmet;
    bool is_alive;
    std::shared_ptr<Gun> gun; // Para polimorfismo
public:
    Duck() : has_chestplate(false), has_helmet(false), is_alive(true) {}
    
    ~Duck() {}

    void pickup_gun(std::shared_ptr<Gun> &gun_ptr) {
        gun = gun_ptr;
    }
};

#endif // SERVER_DUCK_H
