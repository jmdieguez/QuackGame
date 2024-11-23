#include "projectile.h"

class ProjectileBanana : public Projectile
{
private:
    uint16_t trayectory;
    bool collide_wall;

public:
    explicit ProjectileBanana(const Hitbox &h, const std::pair<int, int> &d);
    void move(const std::function<bool(Position &)> &validator) override;
    void cancel_move() override;
    void collide_walls() override;

    ~ProjectileBanana();
};