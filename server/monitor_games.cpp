#include "monitor_games.h"
MonitorGames::MonitorGames()
{
}

std::vector<UserLobbyInfo> MonitorGames::create_game(const uint16_t &creator_id, const std::string &name, const uint16_t &num_players, Socket &skt)
{
    // TODO: Chequear que no existe una partida con mismo nombre
    std::lock_guard<std::mutex> lock(mtx);
    std::vector<UserLobbyInfo> users;
    auto new_game = std::make_shared<Gameloop>(id_counter, name, creator_id);
    Color color = new_game->add_new_player(skt, creator_id);
    users.push_back(UserLobbyInfo(creator_id, color.get_text()));
    if (num_players > 1)
    {
        color = new_game->add_new_player(skt, creator_id + 1);
        users.push_back(UserLobbyInfo((creator_id + 1), color.get_text()));
    }
    games[id_counter] = new_game;
    return users;
}

void MonitorGames::join_game(const uint16_t &player_id, const uint16_t &game_id, Socket &skt)
{
    std::lock_guard<std::mutex> lock(mtx);
    auto it = games.find(game_id);
    if (it != games.end())
    {
        it->second->add_new_player(skt, player_id);
    }
}

std::vector<LobbyMessage> MonitorGames::list_games()
{
    std::lock_guard<std::mutex> lock(mtx);
    std::vector<LobbyMessage> messages;
    for (const auto &[id, game] : games)
    {
        messages.push_back(LobbyMessage(game->get_name(), id));
    }
    return messages;
}

void MonitorGames::start_game(const uint16_t &creator_id, const int &game_id)
{
    std::lock_guard<std::mutex> lock(mtx);
    auto game = games.find(game_id);
    if (game != games.end())
    {
        game->second->start_game(creator_id);
    }
}

void MonitorGames::remove_finished_matches()
{
    std::lock_guard<std::mutex> lock(mtx);

    for (auto it = games.begin(); it != games.end();)
    {
        auto game = it->second;
        if (game == nullptr || game->has_finished())
        {
            if (game != nullptr)
                game->join();
            it = games.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void MonitorGames::remove_all_matches()
{
    std::lock_guard<std::mutex> lock(mtx);
    for (const auto &[id, game] : games)
    {
        game->stop();
        game->join();
    }
}

void MonitorGames::number_of_players(const uint16_t &game_id, uint16_t &amount)
{
    std::lock_guard<std::mutex> lock(mtx);
    auto game = games.find(game_id);
    if (game != games.end())
    {
        game->second->get_number_of_players(amount);
    }
}