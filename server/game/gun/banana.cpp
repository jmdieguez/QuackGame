#include "banana.h"

#define MAX_DISTANCE 10
#define TIME_EXPLOSION 100

#define GUN_WIDTH 15
#define GUN_HEIGHT 15

#define PROJECTILE_WIDTH 15
#define PROJECTILE_HEIGHT 15

#define HORIZONTAL_Y 3
#define HORIZONTAL_RIGHT -10
#define HORIZONTAL_LEFT 10

#define VERTICAL_RIGHT -10
#define VERTICAL_LEFT 6

#define LOOKING_UP_RIGHT_OFFSET_X 0
#define LOOKING_UP_LEFT_OFFSET_X 18

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

Banana::Banana(const uint16_t &id, const Position &position) : Gun(id, GunType::Banana, Position(position), Size(GUN_WIDTH, GUN_HEIGHT), TextureFigure::BananaFigure),
                                                               peeled_banana(false),
                                                               position_gun(HORIZONTAL_Y, HORIZONTAL_RIGHT, HORIZONTAL_LEFT, VERTICAL_RIGHT, VERTICAL_LEFT)
{
}

std::optional<std::pair<std::vector<std::shared_ptr<Projectile>>, Position>> Banana::shoot(bool &looking_right, bool &looking_up, const Position &duck_position)
{
    (void)looking_right;
    (void)looking_up;
    (void)duck_position;
    peeled_banana = true;
    return std::nullopt;
}

Position Banana::get_position_in_duck(const uint16_t &height_duck, const Position &duck, const bool &looking_right, const bool &looking_up)
{
    (void)height_duck;
    (void)looking_up;
    uint16_t pos_x = duck.x + (looking_right ? HORIZONTAL_RIGHT : HORIZONTAL_LEFT);
    uint16_t pos_y = duck.y + HORIZONTAL_Y;
    return Position(pos_x, pos_y);
}

std::shared_ptr<Projectile> Banana::get_projectile(bool &looking_right, bool &looking_up)
{
    (void)looking_up;
    std::pair<int, int> directions = looking_right ? std::make_pair(1, 0) : std::make_pair(-1, 0);
    Hitbox hitbox(position, Size(PROJECTILE_WIDTH, PROJECTILE_HEIGHT));
    return std::make_shared<ProjectileBanana>(hitbox, directions);
}

Banana::~Banana()
{
}
