#ifndef HITBOX_H
#define HITBOX_H

#include "../../common/position.h"
#include "../../common/size.h"

class Hitbox
{
private:
protected:
    Position position;
    Size size;

public:
    Hitbox(const Position &position, const Size &size);
    Position get_position() const;
    Size get_size() const;
    Hitbox get_hitbox() const;
    bool intersects(const Hitbox &other) const;
    ~Hitbox();
};

#endif // HITBOX_H