#include "game.h"
#include "gun/projectile/projectilegrenade.h"

#include <filesystem>

#define MAPS_PATH "/etc/quackgame/maps"
#define MIN_ROUNDS_WON 10
#define N_GUNS 9

namespace fs = std::filesystem;

Game::Game() : rng(rd()), dist(0, N_GUNS - 1)
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

    gun_spawners.push_back([this](const Position &pos)
                           { spawn_gun<AK>(pos); });
    gun_spawners.push_back([this](const Position &pos)
                           { spawn_gun<Shotgun>(pos); });
    gun_spawners.push_back([this](const Position &pos)
                           { spawn_gun<Banana>(pos); });
    gun_spawners.push_back([this](const Position &pos)
                           { spawn_gun<CowboyPistol>(pos); });
    gun_spawners.push_back([this](const Position &pos)
                           { spawn_gun<DuelingPistol>(pos); });
    gun_spawners.push_back([this](const Position &pos)
                           { spawn_gun<Grenade>(pos); });
    gun_spawners.push_back([this](const Position &pos)
                           { spawn_gun<Magnum>(pos); });
    gun_spawners.push_back([this](const Position &pos)
                           { spawn_gun<PewPewLaser>(pos); });
    gun_spawners.push_back([this](const Position &pos)
                           { spawn_gun<Sniper>(pos); });

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

        Position duck_position = duck.get_position();
        Position below_duck(duck_position.x, duck_position.y + 16);
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

        case ClientActionType::BENT_DOWN:
            duck.bent_down();
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
            spawn_gun<AK>(below_duck);
            break;

        case ClientActionType::SPAWN_SHOTGUN:
            spawn_gun<Shotgun>(below_duck);
            break;

        case ClientActionType::SPAWN_GRENADE:
            spawn_gun<Grenade>(below_duck);
            break;

        case ClientActionType::SPAWN_BANANA:
            spawn_gun<Banana>(below_duck);
            break;

        case ClientActionType::SPAWN_COWBOY_PISTOL:
            spawn_gun<CowboyPistol>(duck.get_position());
            break;

        case ClientActionType::SPAWN_DUELING_PISTOL:
            spawn_gun<DuelingPistol>(duck.get_position());
            break;

        case ClientActionType::SPAWN_MAGNUM:
            spawn_gun<Magnum>(duck.get_position());
            break;

        case ClientActionType::SPAWN_PEW_PEW_LASER:
            spawn_gun<PewPewLaser>(duck.get_position());
            break;

        case ClientActionType::SPAWN_SNIPER:
            spawn_gun<Sniper>(duck.get_position());
            break;
        default:
            break;
        }
    }
    catch (const std::out_of_range &e)
    {
    }
}

bool Game::verify_hit_duck(Duck &duck, std::shared_ptr<Projectile> &projectile)
{
    Hitbox projectile_hitbox = projectile->get_hitbox();

    if (projectile->get_type() == ProjectileType::Grenade)
        return false;
    if (projectile->get_type() == ProjectileType::Banana)
    {
        ProjectileBanana *banana = (ProjectileBanana *)projectile.get();
        banana->checkCollision(duck.get_hitbox(), duck.get_duck_status());
        return false;
    }

    if (duck.intersects(projectile_hitbox))
    {
        duck.set_receive_shot();
        projectile->destroy();
        return true;
    }
    return false;
}

bool Game::verify_hit_box(Box &box, const Position &position, std::shared_ptr<Projectile> &projectile)
{
    Hitbox projectile_hitbox = projectile->get_hitbox();
    Size size(TILE_SIZE, TILE_SIZE);
    Position position_as_pixels(position.x * TILE_SIZE, position.y * TILE_SIZE);
    Hitbox box_hitbox(position_as_pixels, size);
    if (box_hitbox.intersects(projectile_hitbox))
    {
        if (box == Box::BOX_1_HP)
        { // Refactorizar en clase
            Position gun_position(position_as_pixels.x, position_as_pixels.y + TILE_SIZE);
            spawn_random_gun(gun_position);
            boxes.erase(position);
        }
        else if (box == Box::BOX_2_HP)
        {
            box = Box::BOX_1_HP;
        }
        else if (box == Box::BOX_3_HP)
        {
            box = Box::BOX_2_HP;
        }
        else if (box == Box::BOX_4_HP)
        {
            box = Box::BOX_3_HP;
        }
        projectile->destroy();
        return true;
    }
    return false;
}

void Game::verify_hits()
{
    for (std::shared_ptr<Projectile> &p : projectiles)
    {
        bool hit = false;
        for (auto &[id, duck] : ducks)
        {
            if (!duck.is_alive())
                continue;
            if (verify_hit_duck(duck, p))
            {
                hit = true;
                break;
            }
        }

        if (!hit)
        {
            for (auto &[position, box] : boxes)
            {
                if (verify_hit_box(box, position, p))
                    break;
            }
        }
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
                explosions.emplace_back(((ProjectileGrenade *)it->get())->get_position_to_explosion());
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

template <typename T>
void Game::spawn_gun(const Position &position_gun)
{
    guns.emplace(gun_id, std::make_shared<T>(gun_id, Position(position_gun.x, position_gun.y - 10)));
    gun_id++;
}

void Game::spawn_random_gun(const Position &position)
{
    int random_index = dist(rng);
    gun_spawners[random_index](position);
}

void Game::move_guns()
{
    for (auto &[id, gun] : guns)
        gun->move([this](Position &p)
                  { return maps[current_map].validate_coordinate(p); });
}

void Game::remove_gun(const uint16_t &id)
{
    guns.erase(id);
}

void Game::spawn_guns()
{
    for (auto &[position, gun_spawn] : gun_spawns)
    {
        Position position_as_pixels(position.x * TILE_SIZE + 2,
                                    position.y * TILE_SIZE + 20);
        if (gun_spawn.step())
        {
            bool spawned = false;

            if (guns.empty())
                spawned = true;
            else
            {
                for (auto &[id, gun] : guns)
                {
                    // Don't spawn a gun if there's one spawned there already
                    if (gun->get_position() == position_as_pixels && !gun->has_been_picked_up())
                        continue;
                    spawned = true;
                    break;
                }
            }

            if (spawned)
            {
                spawn_random_gun(position_as_pixels);
                gun_spawn.restart();
            }
        }
    }
}

void Game::step()
{
    if (initialize)
    {
        guns.clear();
        projectiles.clear();
        boxes.clear();
        explosions.clear();
        gun_spawns.clear();

        for (const auto &position : maps[current_map].get_guns_spawns())
            gun_spawns.emplace(position, GunSpawn());

        for (const auto &position : maps[current_map].get_boxes_spawns())
            boxes.emplace(position, Box::BOX_4_HP);

        spawn_players();
        initialize = false;
    }

    spawn_guns();
    remove_projectiles();
    move_projectiles();
    verify_hits();
    decrement_explosions();
    std::vector<uint8_t> ducks_alive;
    for (auto &[id, duck] : ducks)
    {
        duck.step(maps[current_map], guns, projectiles, sounds);
        if (duck.is_alive())
        {
            ducks_alive.push_back(id);
        }
    }
    move_guns();
    check_for_winner(ducks_alive);
}

Snapshot Game::get_status()
{
    MapSnapshot map_snapshot = maps[current_map].get_status();
    std::vector<GunNoEquippedSnapshot> guns_snapshots;
    std::vector<DuckSnapshot> duck_snapshots;
    std::vector<ExplosionSnapshot> explosions_snapshots;
    std::vector<SoundSnapshot> sound_snapshots;
    std::vector<BoxSnapshot> box_snapshots;
    std::vector<ProjectileSnapshot> projectile_snapshots;

    for (auto &[id, gun] : guns)
    {
        if (!gun.get()->has_been_equipped())
            guns_snapshots.push_back(gun->get_status());
    }

    for (auto &[position, box] : boxes)
        box_snapshots.push_back(BoxSnapshot(position, box));

    for (auto &[id, duck] : ducks)
        duck_snapshots.push_back(duck.get_status());

    for (auto &projectile : projectiles)
        projectile_snapshots.push_back(projectile->get_status());

    for (auto &explosion : explosions)
        explosions_snapshots.push_back(explosion.get_status());

    for (auto &sound : sounds)
        sound_snapshots.push_back(SoundSnapshot(sound));

    sounds.clear();

    return Snapshot(std::move(duck_snapshots), std::move(guns_snapshots), std::move(projectile_snapshots),
                    std::move(explosions_snapshots), std::move(sound_snapshots), std::move(box_snapshots), map_snapshot);
}