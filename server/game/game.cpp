#include "game.h"

Game::Game(const std::string &map_file) : map(map_file)
{
}

void Game::process(ClientCommand &command)
{
    try
    {
        Duck &duck = ducks.at(command.player_id);
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
        for (Projectile &p : projectiles)
        {
            if (!duck.is_in_range(p.get_position()))
                continue;
            duck.set_receive_shot();
            p.destroy();
        }
}

void Game::moves_projectiles(Map &map)
{
    for (Projectile &p : projectiles)
    {
        p.move();
        if (!map.has_something_in(p.get_position()))
            continue;
        p.cancel_move();
        p.destroy();
    }
}

void Game::remove_projectiles()
{
    for (auto it = projectiles.begin(); it != projectiles.end();)
    {
        if (it->is_finish())
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
        projectile_snapshots.push_back(projectile.get_status());
    return Snapshot(std::move(duck_snapshots), std::move(guns_snapshots), std::move(projectile_snapshots), map_snapshot);
}