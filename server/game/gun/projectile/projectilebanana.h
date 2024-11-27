#include "projectile.h"

class ProjectileBanana : public Projectile
{
private:
    DuckStatus &status;
    const Position &duck_position;
    uint16_t trayectory;
    bool is_throwing;
    bool collide_wall;

public:
    explicit ProjectileBanana(DuckStatus &status, const Position &duck_position);
    void move(const std::function<bool(Position &)> &validator) override;
    void throw_banana(bool &looking_right);
    void checkCollision(Hitbox duck, DuckStatus &status);
    ~ProjectileBanana();
};