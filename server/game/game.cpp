#include "game.h"
#include "../../common/config.h"
#include "gun/projectile/projectilegrenade.h"

#include <filesystem>

#ifdef GLOBAL_INSTALL
    #define MAPS_PATH "/etc/quackgame/maps"
#else // LOCAL_INSTALL
    #define MAPS_PATH "server/game/maps"
#endif

#define N_DROPS 11

namespace fs = std::filesystem;

Game::Game() : check_won(Config::getInstance()["settings"]["check_won"].as<unsigned>()),
               min_round_to_win(Config::getInstance()["settings"]["min_round_to_win"].as<unsigned>()),
               rng(rd()), dist(0, N_DROPS - 1)
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
                           { Position aux(pos.x + 2, pos.y - 20);
                             armor.emplace(aux, ArmorType::Helmet); });
    gun_spawners.push_back([this](const Position &pos)
                           { Position aux(pos.x + 2, pos.y - 20); 
                             armor.emplace(aux, ArmorType::Chestplate); });
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
                           { spawn_gun<LaserRifle>(pos); });
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
            duck.move_right();
            break;

        case ClientActionType::MOVE_LEFT:
            duck.move_left();
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
            spawn_gun<CowboyPistol>(below_duck);
            break;

        case ClientActionType::SPAWN_DUELING_PISTOL:
            spawn_gun<DuelingPistol>(below_duck);
            break;

        case ClientActionType::SPAWN_MAGNUM:
            spawn_gun<Magnum>(below_duck);
            break;

        case ClientActionType::SPAWN_PEW_PEW_LASER:
            spawn_gun<PewPewLaser>(below_duck);
            break;

        case ClientActionType::SPAWN_SNIPER:
            spawn_gun<Sniper>(below_duck);
            break;

        case ClientActionType::SPAWN_LASER_RIFLE:
            spawn_gun<LaserRifle>(below_duck);
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
        banana->check_collision(duck.get_hitbox(), duck.get_duck_status());
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

void Game::spawn_in_boxes(const Position &position_box, const Position &position_as_pixels)
{

    Position position(position_as_pixels.x, position_as_pixels.y + TILE_SIZE);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 2); // Range [0, 2]
    RandomSelection random_selection = static_cast<RandomSelection>(distrib(gen));
    switch (random_selection)
    {
    case RandomSelection::Nothing:
        break;
    case RandomSelection::SpawnGun:
        spawn_random_gun(position);
        break;
    case RandomSelection::Explode:
        Explosion explosion(position_as_pixels);
        explosions.add_explosion(explosion);
        break;
    }
    boxes.erase(position_box);
}

void Game::check_intersect(Hitbox explosion_hitbox)
{
    for (auto &[id, duck] : ducks)
    {
        if (!duck.intersects(explosion_hitbox))
            continue;
        duck.set_receive_shot();
    }
}

int Game::calculate_winner(const std::vector<uint8_t> &possible_winners)
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

void Game::check_for_winner(const std::map<uint8_t, Duck &> &ducks_alive)
{
    int n_ducks_alive = ducks_alive.size();
    if (n_ducks_alive <= 1)
    {
        initialize = true;
        current_map = (++round) % maps.size();
        if (n_ducks_alive == 1)
        {
            auto winner = ducks_alive.begin();
            ++victories[winner->first];
            if ((round >= check_won) && (round % check_won == 0))
            { // Check if somebody won every five rounds
                std::vector<uint8_t> possible_winners;
                for (const auto &[id, n_victories] : victories)
                {
                    if (n_victories >= min_round_to_win)
                        possible_winners.push_back(id);
                }

                if (possible_winners.size() > 0)
                {
                    int winner = calculate_winner(possible_winners);

                    if (winner != -1)
                    {
                        winner_id = winner;
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
    Size spawn_size(TILE_SIZE, TILE_SIZE);

    for (auto &[position, gun_spawn] : gun_spawns)
    {
        Position position_as_pixels(position.x * TILE_SIZE,
                                    position.y * TILE_SIZE);
        Hitbox gun_spawn_hitbox(position_as_pixels, spawn_size);
        if (gun_spawn.step())
        {
            bool spawn = true;
            if (!guns.empty())
            {
                for (auto &[id, gun] : guns)
                {
                    if (gun->intersects(gun_spawn_hitbox) && !gun->has_been_picked_up())
                    {
                        gun_spawn.restart();
                        spawn = false;
                        break;
                    }
                }

                for (auto &[position, type] : armor)
                {
                    Hitbox hitbox(position, spawn_size);
                    if (gun_spawn_hitbox.intersects(hitbox))
                    {
                        gun_spawn.restart();
                        spawn = false;
                        break;
                    }
                }
            }

            if (spawn)
            {
                Position gun_position(position_as_pixels.x + 2,
                                      position_as_pixels.y + 20);
                spawn_random_gun(gun_position);
                gun_spawn.restart();
            }
        }
    }
}

void Game::update_camera(std::map<uint8_t, Duck &> &ducks)
{
    if (ducks.empty())
        return;

    int min_x = 99999, max_x = 0, acum_y = 0;

    for (const auto &[_, duck] : ducks)
    {
        Position pos = duck.get_position();
        acum_y += pos.y;
        if (pos.x > max_x)
            max_x = pos.x;
        if (pos.x < min_x)
            min_x = pos.x;
    }

    max_x = std::min(1024, max_x + PADDING);
    camera.x = std::max(0, min_x - PADDING);
    camera.width = std::max(MIN_CAMERA_WIDTH, max_x - camera.x);
    camera.height = std::max(MIN_CAMERA_HEIGHT, camera.width * 9 / 16);
    camera.y = std::max(0, static_cast<int>((acum_y / ducks.size()) - (camera.height / 2)));
    if (camera.x + camera.width > 1024)
        camera.x = 1024 - camera.width;
    if (camera.y + camera.height > 576)
        camera.y = 576 - camera.height;
}

void Game::step()
{
    if (initialize)
    {
        guns.clear();
        boxes.clear();
        projectiles.get_projectiles().clear();
        explosions.get_explosions().clear();
        gun_spawns.clear();
        armor.clear();

        for (const auto &position : maps[current_map].get_guns_spawns())
            gun_spawns.emplace(position, GunSpawn());

        for (const auto &position : maps[current_map].get_boxes_spawns())
            boxes.emplace(position, Box::BOX_4_HP);

        spawn_players();
        initialize = false;
    }

    spawn_guns();
    projectiles.remove([this](std::vector<std::shared_ptr<Projectile>>::iterator it)
                       { Explosion explosion(((ProjectileGrenade *)it->get())->get_position_to_explosion());
                        explosions.add_explosion(explosion); });
    projectiles.move(maps[current_map]);
    projectiles.verify_hit(ducks, boxes, [this](const Position &p_box, const Position &p_as_pixels)
                           { spawn_in_boxes(p_box, p_as_pixels); });
    explosions.dicrement([this](const std::shared_ptr<Projectile> &projectile)
                         { projectiles.add_projectile(projectile); }, [this](Hitbox explosion_hitbox)
                         { check_intersect(explosion_hitbox); });

    Size size(TILE_SIZE, TILE_SIZE); // Ajustar
    std::map<uint8_t, Duck &> ducks_alive;
    for (auto &[id, duck] : ducks)
    {
        duck.step(maps[current_map], guns, [this](const std::shared_ptr<Projectile> &projectile)
                  { projectiles.add_projectile(projectile); });
        if (duck.is_alive())
        {
            ducks_alive.emplace(id, duck);
            for (auto it = armor.begin(); it != armor.end();)
            {
                const auto &position = it->first;
                const auto &an_armor = it->second;

                Hitbox armor_hitbox(position, size);
                if (duck.get_hitbox().intersects(armor_hitbox))
                {
                    if (an_armor == ArmorType::Helmet)
                        duck.give_helmet();
                    else if (an_armor == ArmorType::Chestplate)
                        duck.give_chestplate();
                    it = armor.erase(it);
                }
                else
                    ++it;
            }
        }
    }
    update_camera(ducks_alive);
    move_guns();
    check_for_winner(ducks_alive);
}

Snapshot Game::get_status()
{
    MapSnapshot map_snapshot = maps[current_map].get_status();
    std::vector<GunNoEquippedSnapshot> guns_snapshots;
    std::vector<DuckSnapshot> duck_snapshots;
    std::vector<BoxSnapshot> box_snapshots;
    std::vector<ProjectileSnapshot> projectile_snapshots;
    std::vector<ArmorSnapshot> armor_snapshots;
    std::vector<DuckScore> scores;
    CameraSnapshot camera_snapshot(camera.x, camera.y, camera.width, camera.height);
    for (auto &[id, gun] : guns)
    {
        if (!gun.get()->has_been_equipped())
            guns_snapshots.push_back(gun->get_status());
    }

    for (const auto &[position, box] : boxes)
        box_snapshots.push_back(BoxSnapshot(position, box));

    for (auto &[id, duck] : ducks)
        duck_snapshots.push_back(duck.get_status());

    for (const auto& victory : victories) {
        uint8_t playerId = victory.first;
        uint8_t victoryCount = victory.second;

        auto colorIt = colors.find(playerId);
        if (colorIt != colors.end()) {
            scores.push_back(DuckScore(victoryCount, colorIt->second));
        }
    }

    return Snapshot(std::move(duck_snapshots), std::move(guns_snapshots), projectiles.get_status(),
                    explosions.get_status(), std::move(box_snapshots), std::move(armor_snapshots), std::move(scores),
                    map_snapshot, camera_snapshot, ended, winner_id, round);
}