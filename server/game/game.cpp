#include "game.h"
#include "gun/projectile/projectilegrenade.h"

Game::Game(const std::string &map_file) : map(map_file)
{
}

void Game::process(ClientCommand &command)
{
    try
    {
        Duck &duck = ducks.at(command.player_id);
        if (!duck.get_status().status.is_alive)
            return;
        switch (command.message.type)
        {
        case ClientActionType::MOVE_RIGHT:
            duck.move(Direction::RIGHT);
            break;

        case ClientActionType::MOVE_LEFT:
            duck.move(Direction::LEFT);
            break;

        case ClientActionType::STOP_MOVING_LEFT:
            duck.stop_moving();
            break;

        case ClientActionType::STOP_MOVING_RIGHT:
            duck.stop_moving();
            break;

        case ClientActionType::FLAP:
            duck.flap();
            break;

        case ClientActionType::JUMP:
            duck.jump();
            break;

        case ClientActionType::SHOOT:
            duck.shoot();
            break;

        case ClientActionType::STOP_SHOOTING:
            duck.stop_shooting();
            break;

        case ClientActionType::LOOK_UP:
            duck.look_up();
            break;

        case ClientActionType::STOP_LOOKING_UP:
            duck.stop_looking_up();
            break;

        case ClientActionType::LAY:
            duck.lay();
            break;

        case ClientActionType::STAND_UP:
            duck.stand_up();
            break;

        case ClientActionType::DROP:
            duck.get_gun_type() == GunType::Grenade ? duck.drop_gun(projectiles) : duck.drop_gun();
            break;
        default:
            break;
        }
    }
    catch (const std::out_of_range &e)
    {
        ducks.emplace(command.player_id, Duck(command.player_id, 256, 250));
    }
}

void Game::verify_hit_ducks()
{
    for (auto &[id, duck] : ducks)
        for (std::shared_ptr<Projectile> &p : projectiles)
        {
            Position current_position = p->get_position();
            if (!duck.is_in_range(current_position))
                continue;
            duck.set_receive_shot();
            p->destroy();
        }
}

void Game::move_grenade(std::shared_ptr<Projectile> &p)
{
    p->move();
    ProjectileGrenade *grenade = (ProjectileGrenade *)p.get();
    Position current_position = p->get_position();
    grenade->reduce_time();
    if (grenade->is_finish())
    {
        Position fragment_left(current_position.pos_x - (5 * TILE_SIZE), current_position.pos_y);
        Position fragment_right(current_position.pos_x + (5 * TILE_SIZE), current_position.pos_y);
        Explosion explosion(current_position);
        explosions.push_back(explosion);
        if (map.validate_coordinate(fragment_left))
        {
            Explosion explosion_left(fragment_left);
            explosions.push_back(explosion_left);
        }
        if (map.validate_coordinate(fragment_right))
        {
            Explosion explosion_right(fragment_right);
            explosions.push_back(explosion_right);
        }
        return;
    }
    if (map.validate_coordinate(current_position))
        return;
    if (grenade->is_change_direction_apply())
    {
        grenade->cancel_move();
        return;
    }
    grenade->collide_walls();
    grenade->cancel_move();
}

void Game::moves_projectiles(Map &map)
{
    for (std::shared_ptr<Projectile> &p : projectiles)
    {
        if (p->get_type() == ProjectileType::Grenade)
        {
            move_grenade(p);
            continue;
        }
        p->move();
        Position current_position = p->get_position();
        if (map.validate_coordinate(current_position))
            continue;
        p->cancel_move();
        p->destroy();
    }
}

void Game::remove_projectiles()
{
    for (auto it = projectiles.begin(); it != projectiles.end();)
    {
        if (it->get()->is_finish())
        {
            it = projectiles.erase(it);
            continue;
        }
        ++it;
    }
}

void Game::step()
{
    remove_projectiles();
    moves_projectiles(map);
    verify_hit_ducks();
    for (auto &[id, duck] : ducks)
        duck.step(map, projectiles);
}

Snapshot Game::get_status()
{
    MapSnapshot map_snapshot = map.get_status();
    std::vector<GunNoEquippedSnapshot> guns_snapshots = map.get_guns_snapshots();
    std::vector<DuckSnapshot> duck_snapshots;
    for (auto &[id, duck] : ducks)
        duck_snapshots.push_back(duck.get_status());
    std::vector<ProjectileSnapshot> projectile_snapshots;
    for (auto &projectile : projectiles)
        projectile_snapshots.push_back(projectile->get_status());
    return Snapshot(std::move(duck_snapshots), std::move(guns_snapshots), std::move(projectile_snapshots), map_snapshot);
}