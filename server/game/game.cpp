#include "game.h"
#include "gun/projectile/projectilegrenade.h"

#include <filesystem>

#define MAPS_PATH "/etc/quackgame/maps"
#define MIN_ROUNDS_WON 10

namespace fs = std::filesystem;

Game::Game()
{
    try
    {
        for (const auto &entry : fs::directory_iterator(MAPS_PATH))
        {
            maps.push_back(Map(entry.path()));
        }
    }
    catch (const fs::filesystem_error &e)
    {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return;
}

void Game::add_player(const uint16_t &id, Color color)
{
    player_ids.push_back(id);
    victories.emplace(id, 0);
    colors.emplace(id, color);
}

void Game::spawn_players()
{
    std::vector<Position> spawns = maps[current_map].calculate_spawns(player_ids.size());
    unsigned i = 0;
    ducks.clear();
    while (i < player_ids.size())
    {
        Position p = spawns[i];
        uint8_t id = player_ids[i++];
        ducks.emplace(id, Duck(id, p, colors[id]));
    }
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
            duck.drop_gun();
            break;

        case ClientActionType::GRAB:
            duck.grab();
            break;

        case ClientActionType::SPAWN_AK:
            maps[current_map].cheat_spawn_gun<AK>(duck.get_position());
            break;

        case ClientActionType::SPAWN_SHOTGUN:
            maps[current_map].cheat_spawn_gun<Shotgun>(duck.get_position());
            break;

        case ClientActionType::SPAWN_GRENADE:
            maps[current_map].cheat_spawn_gun<Grenade>(duck.get_position());
            break;

        case ClientActionType::SPAWN_BANANA:
            maps[current_map].cheat_spawn_gun<Banana>(duck.get_position());
            break;
        default:
            break;
        }
    }
    catch (const std::out_of_range &e)
    {
    }
}

void Game::verify_hit_ducks()
{
    for (auto &[id, duck] : ducks)
        for (std::shared_ptr<Projectile> &p : projectiles)
        {
            if (p->get_type() == ProjectileType::Grenade)
                continue;
            if (p->get_type() == ProjectileType::Banana)
            {
                ProjectileBanana *banana = (ProjectileBanana *)p.get();
                banana->checkCollision(duck.get_hitbox(), duck.get_duck_status());
                continue;
            }
            Hitbox proctile_hitbox = p->get_hitbox();
            if (!duck.intersects(proctile_hitbox))
                continue;
            duck.set_receive_shot();
            p->destroy();
        }
}

void Game::move_projectiles()
{
    for (std::shared_ptr<Projectile> &p : projectiles)
    {
        p->move([this](Position &p)
                { return maps[current_map].validate_coordinate(p); });
    }
}

void Game::remove_projectiles()
{
    for (auto it = projectiles.begin(); it != projectiles.end();)
    {
        if (it->get()->is_finish())
        {
            if (it->get()->get_type() == ProjectileType::Grenade)
            {
                explosions.emplace_back(it->get()->get_position());
            }
            it = projectiles.erase(it);
            continue;
        }
        it++;
    }
}

void Game::decrement_explosions()
{
    for (auto it = explosions.begin(); it != explosions.end();)
    {
        if (it->is_finish())
        {
            for (auto &[id, duck] : ducks)
            {
                Hitbox proctile_hitbox = it->get_hitbox();
                if (!duck.intersects(proctile_hitbox))
                    continue;
                duck.set_receive_shot();
            }
            it->add_fragments(projectiles);
            it = explosions.erase(it);
            continue;
        }
        it->time_decrement();
        it++;
    }
}

int Game::calculate_winner(std::vector<uint8_t> possible_winners)
{
    int max_score = 0;
    std::vector<uint8_t> winners;
    for (const auto &id : possible_winners)
    {
        int score = victories[id];
        if (score > max_score)
        {
            max_score = score;
            winners = {id};
        }
        else if (score == max_score)
        {
            winners.push_back(id);
        }
    }

    if (winners.size() > 1)
        return -1; // Exception

    return winners[0];
}

void Game::check_for_winner(const std::vector<uint8_t> &ducks_alive)
{
    int n_ducks_alive = ducks_alive.size();
    if (n_ducks_alive <= 1)
    {
        initialize = true;
        current_map = (++round) % maps.size();
        if (n_ducks_alive == 1)
        {
            ++victories[ducks_alive[0]];
            if ((round >= 5) && (round % 5 == 0))
            { // Check if somebody won every five rounds
                std::vector<uint8_t> possible_winners;
                for (const auto &[id, n_victories] : victories)
                {
                    if (n_victories >= MIN_ROUNDS_WON)
                    {
                        possible_winners.push_back(id);
                    }
                }

                if (possible_winners.size() > 0)
                {
                    int winner = calculate_winner(possible_winners);

                    if (winner != -1)
                    {
                        ended = true;
                    }
                }
            }
        }
    }
}

void Game::step()
{
    if (initialize)
    {
        spawn_players();
        initialize = false;
    }

    remove_projectiles();
    move_projectiles();
    verify_hit_ducks();
    decrement_explosions();
    std::vector<uint8_t> ducks_alive;
    for (auto &[id, duck] : ducks)
    {
        duck.step(maps[current_map], projectiles, sounds);
        if (duck.is_alive())
        {
            ducks_alive.push_back(id);
        }
    }
    maps[current_map].move_guns();

    check_for_winner(ducks_alive);
}

Snapshot Game::get_status()
{
    MapSnapshot map_snapshot = maps[current_map].get_status();
    std::vector<GunNoEquippedSnapshot> guns_snapshots = maps[current_map].get_guns_snapshots();
    std::vector<DuckSnapshot> duck_snapshots;
    std::vector<ExplosionSnapshot> explosions_snapshots;
    std::vector<SoundSnapshot> sound_snapshots;
    for (auto &[id, duck] : ducks)
        duck_snapshots.push_back(duck.get_status());
    std::vector<ProjectileSnapshot> projectile_snapshots;
    for (auto &projectile : projectiles)
        projectile_snapshots.push_back(projectile->get_status());
    for (auto &explosion : explosions)
        explosions_snapshots.push_back(explosion.get_status());
    for (auto &sound : sounds)
        sound_snapshots.push_back(SoundSnapshot(sound));
    sounds.clear();
    return Snapshot(std::move(duck_snapshots), std::move(guns_snapshots), std::move(projectile_snapshots),
                    std::move(explosions_snapshots), std::move(sound_snapshots), map_snapshot);
}