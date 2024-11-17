

#include "monitor_games.h"
MonitorGames::MonitorGames()
{
}

void MonitorGames::create_game(const uint16_t &creator_id, const std::string &name, Queue<Snapshot> &queue)
{
    // TODO: Chequear que no existe una partida con mismo nombre
    std::lock_guard<std::mutex> lock(mtx);
    auto newGame = std::make_shared<Gameloop>(id_counter, name, creator_id);
    newGame->add_new_player(creator_id, queue);
    games[id_counter] = newGame;
    player_to_game[creator_id] = id_counter;
    id_counter++;
}

Queue<ClientCommand> *MonitorGames::add_player(const uint16_t &game_id, const uint16_t &creator_id, Queue<Snapshot> &queue)
{
    std::lock_guard<std::mutex> lock(mtx);
    Queue<ClientCommand> *game_q = nullptr;
    auto it = games.find(game_id);
    if (it != games.end())
    {
        game_q = it->second->add_new_player(creator_id, queue);
        player_to_game[creator_id] = game_id;
    }
    return game_q;
}

Queue<ClientCommand> *MonitorGames::start_game(const uint16_t &creator_id)
{
    std::lock_guard<std::mutex> lock(mtx);

    auto playerIt = player_to_game.find(creator_id);
    if (playerIt == player_to_game.end())
    {
        return nullptr;
    }

    uint16_t game_id = playerIt->second;

    auto gameIt = games.find(game_id);
    if (gameIt != games.end())
    {
        return gameIt->second->start_game(creator_id);
    }
    return nullptr;
}

void MonitorGames::list_games(Queue<LobbyMessage> &queue, uint16_t &game_size)
{
    std::lock_guard<std::mutex> lock(mtx);
    game_size = games.size();
    for (const auto &[id, gameloop_ptr] : games)
    {
        if (gameloop_ptr)
        {
            std::string name = gameloop_ptr->get_name();
            queue.push(LobbyMessage(name, id));
        }
    }
}
