#ifndef BANANA_H
#define BANANA_H
#include "gun.h"
#include "positiongun.h"
#include "projectile/projectilebanana.h"

class Banana : public Gun
{
private:
    bool peeled_banana;
    PositionGun position_gun;

public:
    explicit Banana(const uint16_t &id, const Position &position);
    std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> shoot(DuckStatus &status, const Position &duck_position) override;
    Position get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up) override;
    std::shared_ptr<Projectile> get_projectile(bool &looking_right, bool &looking_up);
    ~Banana();
};

#endif // BANANA_H