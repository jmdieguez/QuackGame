#ifndef SERVER_DUCK_H
#define SERVER_DUCK_H

#include <functional>
#include <memory>
#include <utility>

#include "movecontroller.h"
#include "guncontroller.h"
#include "../gun/gun.h"
#include "../map.h"
#include "../hitbox.h"
#include "../../../common/color.h"
#include "../../../common/duck.h"
#include "../../../common/direction.h"
#include "../../../common/snapshots.h"

class Duck : public Hitbox, public GunController, public MoveController
{
private:
    uint8_t id;
    DuckStatus status;
    Color color;
    int y_velocity;
    bool set_is_alive;

    void process_movement(Map &map);
    void process_shooting(Map &map,
                          std::map<uint8_t, std::shared_ptr<Gun>> &guns,
                          const std::function<void(const std::shared_ptr<Projectile> &)> &add_projectile);

public:
    explicit Duck(const uint8_t &i, const Position &p, const Color &color);
    ~Duck();

    // Actions
    void move(Direction d);
    void stop_moving();
    void look_up();
    void stop_looking_up();
    void drop_gun();
    void shoot();
    void stop_shooting();
    void bent_down();
    void jump();
    void stand_up();
    void set_receive_shot();
    void grab();
    DuckStatus &get_duck_status();

    // Get current duck snapshot
    DuckSnapshot get_status();

    bool is_alive() const;

    // Simulate an iteration
    void step(Map &map,
              std::map<uint8_t, std::shared_ptr<Gun>> &guns,
              const std::function<void(const std::shared_ptr<Projectile> &)> &add_projectile);
};

#endif // SERVER_DUCK_H
