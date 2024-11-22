#include "guncontroller.h"

GunController::GunController() : gun(nullptr), block_shooting_command(false) {}

GunType GunController::get_gun_type()
{
    return gun == nullptr ? GunType::None : gun->get_type();
}

TextureFigure GunController::get_gun_texture()
{
    return gun == nullptr ? TextureFigure::CowboyPistolFigure : gun->get_texture();
}

uint16_t GunController::get_gun_angle(DuckStatus &status) const
{
    return gun == nullptr ? 0 : gun->get_angle(status.looking_right, status.looking_up);
}

Size GunController::get_gun_size() const
{
    return gun == nullptr ? Size(0, 0) : gun->get_size();
}

void GunController::finish_shooting()
{
    if (gun->get_type() == GunType::Shotgun)
        ((Shotgun *)gun.get())->check_reset();
    if (gun->get_type() == GunType::Sniper)
        ((Sniper *)gun.get())->check_reset();
    if (gun->get_type() == GunType::AK)
        ((AK *)gun.get())->check_reset();
}

Position GunController::get_gun_position(Position &position, Size &size, DuckStatus &status) const
{
    return gun == nullptr ? Position(0, 0) : gun->get_position_in_duck(size.height, position, status.looking_right, status.looking_up);
}

void GunController::discard_gun(Map &map, Position &position, Size &size, DuckStatus &status)
{
    Position pos = get_gun_position(position, size, status);
    gun->dropped(pos);
    map.add_gun(gun);
    gun = nullptr;
    status.gun_drop = false;
}

void GunController::pick_up(Map &map, DuckStatus &status, const std::function<bool(const Hitbox &)> &func)
{
    std::optional<uint8_t> id_to_erase;
    for (auto &[id, gun] : map.get_guns())
    {
        Hitbox gun_hitbox = gun->get_hitbox();
        if (!func(gun_hitbox))
            continue;
        id_to_erase = id;
        this->gun = gun;
    }
    if (id_to_erase.has_value())
        map.get_guns().erase(id_to_erase.value());
    status.gun_grab = false;
}

void GunController::drop_grenade(DuckStatus &status, std::vector<std::shared_ptr<Projectile>> &projectiles)
{
    Grenade *grenade = (Grenade *)gun.get();
    projectiles.push_back(grenade->get_projectile(status.looking_right, status.looking_up));
    gun = nullptr;
    status.gun_drop = false;
}

void GunController::fire(DuckStatus &status, Position &position, Map &map,
                         std::vector<std::shared_ptr<Projectile>> &projectiles,
                         std::vector<SoundType> &sounds)
{
    auto result = gun->shoot(status.looking_right, status.looking_up, position);
    if (!result.has_value())
    {
        if ((gun->get_type() == GunType::Shotgun && ((Shotgun *)gun.get())->is_block_shoot()) ||
            (gun->get_type() == GunType::Sniper && ((Sniper *)gun.get())->is_block_shoot()))
        {
            block_shooting_command = true;
        }
        return;
    }
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
    for (std::shared_ptr<Projectile> p : shot_projectile)
    {
        projectiles.push_back(p);
        sounds.push_back(SoundType::SHOOT);
    }

    if ((gun->get_type() == GunType::Shotgun && !((Shotgun *)gun.get())->is_block_shoot()) ||
        (gun->get_type() == GunType::Sniper && !((Sniper *)gun.get())->is_block_shoot()) ||
        gun->get_type() == GunType::AK)
    {
        return;
    }
    block_shooting_command = true;
}

GunController::~GunController() {}