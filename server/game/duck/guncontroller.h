#include <memory>
#include <utility>
#include <functional>

#include "../map.h"
#include "../gun/gun.h"
#include "../gun/ak.h"
#include "../gun/shotgun.h"
#include "../../../common/position.h"
#include "../../../common/duck.h"

class GunController
{
private:
public:
    std::shared_ptr<Gun> gun;
    bool block_shooting_command;

    explicit GunController() : gun(nullptr), block_shooting_command(false) {};

    void stop_shooting(DuckStatus &status)
    {
        if (gun == nullptr)
            return;
        status.shooting = false;
        block_shooting_command = false;
        if (gun->get_type() == GunType::Shotgun)
            ((Shotgun *)gun.get())->check_reset();
        if (gun->get_type() == GunType::Sniper)
            ((Sniper *)gun.get())->check_reset();
        if (gun->get_type() == GunType::AK)
            ((AK *)gun.get())->check_reset();
    }

    Position get_gun_position(Position &position, Size &size, DuckStatus &status) const
    {
        return gun == nullptr ? Position(0, 0) : gun->get_position_in_duck(size.height, position, status.looking_right, status.looking_up);
    }

    void drop_gun(Map &map, Position &position, Size &size, DuckStatus &status)
    {
        if (!gun)
            return;
        Position pos = get_gun_position(position, size, status);
        gun->dropped(pos);
        map.add_gun(gun);
        gun = nullptr;
    }

    void shoot(DuckStatus &status, Position &position, Map &map, std::vector<std::shared_ptr<Projectile>> &projectiles, std::vector<SoundType> &sounds)
    {

        auto result = gun->shoot(status.looking_right, status.looking_up, position);
        if (!result.has_value() && gun->get_type() == GunType::Shotgun && (((Shotgun *)gun.get())->is_block_shoot()))
        {
            block_shooting_command = true;
            return;
        }
        if (!result.has_value() && gun->get_type() == GunType::Sniper && (((Sniper *)gun.get())->is_block_shoot()))
        {
            block_shooting_command = true;
            return;
        }
        if (!result.has_value())
            return;
        std::vector<std::shared_ptr<Projectile>> shot_projectile = result.value().first;
        Position duck_position_after_shoot = result.value().second;
        if (duck_position_after_shoot.x != position.x || duck_position_after_shoot.y != position.y)
        {
            if (duck_position_after_shoot.x != position.x)
            {
                int start_x = std::min(position.x, duck_position_after_shoot.x);
                int end_x = std::max(position.x, duck_position_after_shoot.x);
                for (int x = status.looking_right ? end_x : start_x;
                     status.looking_right ? x >= start_x : x <= end_x;
                     status.looking_right ? --x : ++x)
                {
                    {
                        Position new_position(x, position.y);
                        if (map.validate_coordinate(new_position))
                        {
                            position.x = (uint16_t)x;
                            continue;
                        }
                        break;
                    }
                }
                if (duck_position_after_shoot.y != position.y)
                {
                    int start_y = std::min(position.y, duck_position_after_shoot.y);
                    int end_y = std::max(position.y, duck_position_after_shoot.y);
                    for (int y = start_y; y <= end_y; ++y)
                    {
                        Position new_position(position.x, y);
                        if (map.validate_coordinate(new_position))
                        {
                            position.y = y;
                            continue;
                        }

                        break;
                    }
                }
            }
        }
        for (std::shared_ptr<Projectile> p : shot_projectile)
        {
            projectiles.push_back(p);
            sounds.push_back(SoundType::SHOOT);
        }

        if (gun->get_type() == GunType::Shotgun && !(((Shotgun *)gun.get())->is_block_shoot()))
            return;
        if (gun->get_type() == GunType::Sniper && !(((Sniper *)gun.get())->is_block_shoot()))
            return;
        if (gun->get_type() == GunType::AK)
            return;
        block_shooting_command = true;
    }

    ~GunController() {};
};
