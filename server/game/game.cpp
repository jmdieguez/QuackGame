#include "game.h"
#include "gun/projectile/projectilegrenade.h"

Game::Game(const std::string &map_file) : map(map_file), spawns(map.calculate_spawns(required_players)) {}

void Game::add_player(const uint16_t &id) {
    Position p = spawns[current_players++];
    ducks.emplace(id, Duck(id, p));
    if (current_players == required_players)
        started = true;
}

void Game::process(ClientCommand &command)
{   
    try {
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
            duck.get_gun_type() == GunType::Grenade ? duck.drop_gun(projectiles) : duck.drop_gun(map);
            break;

        case ClientActionType::GRAB:
            duck.grab(map);
            break;

        case ClientActionType::SPAWN_AK:
            map.add_new_gun_ak(duck.get_position());
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
            Hitbox proctile_hitbox = p->get_hitbox();
            if (!duck.intersects(proctile_hitbox))
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
        Position fragment_left(current_position.x - (5 * TILE_SIZE), current_position.y);
        Position fragment_right(current_position.x + (5 * TILE_SIZE), current_position.y);
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
        it++;
    }
}

void Game::step()
{
    remove_projectiles();
    moves_projectiles(map);
    verify_hit_ducks();
    for (auto &[id, duck] : ducks)
        duck.step(map, projectiles, sounds);
    map.move_guns();
}

Snapshot Game::get_status()
{
    MapSnapshot map_snapshot = map.get_status();
    std::vector<GunNoEquippedSnapshot> guns_snapshots = map.get_guns_snapshots();
    std::vector<DuckSnapshot> duck_snapshots;
    std::vector<SoundSnapshot> sound_snapshots;
    for (auto &[id, duck] : ducks)
        duck_snapshots.push_back(duck.get_status());
    std::vector<ProjectileSnapshot> projectile_snapshots;
    for (auto &projectile : projectiles)
        projectile_snapshots.push_back(projectile->get_status());
    for (auto &sound : sounds)
        sound_snapshots.push_back(SoundSnapshot(sound));
    sounds.clear();
    return Snapshot(std::move(duck_snapshots), std::move(guns_snapshots), std::move(projectile_snapshots), std::move(sound_snapshots), map_snapshot);
}