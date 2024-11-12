#include "hitbox.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Hitbox::Hitbox(const Position &position, const Size &size) : position(position), size(size)
{
}
Position Hitbox::get_position() const
{
    return position;
}
Size Hitbox::get_size() const
{
    return size;
}
Hitbox Hitbox::get_hitbox() const
{
    return Hitbox(position, size);
}
bool Hitbox::intersects(const Hitbox &other) const
{
    Position other_position = other.get_position();
    Size other_size = other.get_size();

    return !(position.x + size.width <= other_position.x || other_position.x + other_size.width <= position.x ||
             position.y + size.height <= other_position.y || other_position.y + other_size.height <= position.y);
}

Hitbox::~Hitbox()
{
}
