#include "projectile.h"

class ProjectileBanana : public Projectile
{
private:
    uint16_t trayectory;
    bool collide_wall;

public:
    explicit ProjectileBanana(const Hitbox &h, const std::pair<int, int> &d);
    void move(const std::function<bool(Position &)> &validator) override;

    void checkCollision(Hitbox duck, DuckStatus &status);

    ~ProjectileBanana();
};