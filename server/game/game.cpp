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

        default:
            break;
        }
    }
    catch (const std::out_of_range &e)
    {
        ducks.emplace(command.player_id, Duck(command.player_id, 128, 128));
    }
}

void Game::step()
{
    for (auto &[id, duck] : ducks)
        duck.step(map);
}

Snapshot Game::get_status()
{
    MapSnapshot map_snapshot = map.get_status();
    std::vector<DuckSnapshot> duck_snapshots;
    std::vector<GunNoEquippedSnapshot> guns_snapshots;
    for (auto &[id, duck] : ducks)
        duck_snapshots.push_back(duck.get_status());

    // Colocar en map.get_status cuando se envie el mapa al cliente
    for (auto &[id, gun] : map.get_guns())
    {
        if (gun.get()->has_been_equipped())
            continue;
        guns_snapshots.push_back(gun.get()->get_status());
    }

    return Snapshot(std::move(duck_snapshots), std::move(guns_snapshots));
}