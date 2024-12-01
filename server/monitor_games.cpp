#include "monitor_games.h"
MonitorGames::MonitorGames()
{
}

std::vector<UserLobbyInfo> MonitorGames::create_game(const uint16_t &creator_id, const std::string &name, const uint16_t &num_players)
{
    // TODO: Chequear que no existe una partida con mismo nombre
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "La cantidad de players es: " << (int)num_players << std::endl;
    id_counter++;
    std::vector<UserLobbyInfo> users;
    auto new_game = std::make_shared<Gameloop>(id_counter, name, creator_id);
    std::vector<uint16_t> ids = (num_players == 1)
                                    ? std::vector<uint16_t>{creator_id}
                                    : std::vector<uint16_t>{creator_id, static_cast<uint16_t>(creator_id + 1)};
    std::vector<Color> colors = new_game->add_new_player(ids);
    for (int i = 0; i < num_players; i++)
        users.push_back(UserLobbyInfo(ids[i], colors[i].get_text()));
    games[id_counter] = new_game;
    return users;
}

void MonitorGames::set_session(const uint16_t &creator_id, const uint16_t &num_players, Socket &skt)
{
    std::vector<uint16_t> ids = (num_players == 1)
                                    ? std::vector<uint16_t>{creator_id}
                                    : std::vector<uint16_t>{creator_id, static_cast<uint16_t>(creator_id + 1)};
    games[id_counter]->set_session(skt, ids);
}

void MonitorGames::join_game(const uint16_t &player_id, const uint16_t &game_id, Socket &skt)
{
    std::lock_guard<std::mutex> lock(mtx);
    std::vector<uint16_t> ids = {player_id};
    auto it = games.find(game_id);
    if (it != games.end())
    {
        it->second->add_new_player(ids);
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

void MonitorGames::start_game(const uint16_t &creator_id, const int &game_id, const uint16_t &num_players, Socket &skt)
{
    std::lock_guard<std::mutex> lock(mtx);
    auto game = games.find(game_id);
    if (game != games.end())
    {
        set_session(creator_id, num_players, skt);
        game->second->start_game(creator_id);
    }
}

uint16_t MonitorGames::get_id_counter() const
{
    return id_counter;
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