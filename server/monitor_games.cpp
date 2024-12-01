#include "monitor_games.h"
MonitorGames::MonitorGames()
{
}

std::vector<UserLobbyInfo> MonitorGames::create_game(const uint16_t &creator_id, const std::string &name, const uint16_t &num_players)
{
    // TODO: Chequear que no existe una partida con mismo nombre
    std::lock_guard<std::mutex> lock(mtx);
    id_counter++;
    std::vector<UserLobbyInfo> users;
    auto new_game = std::make_shared<Gameloop>(id_counter, name, creator_id);
    for (size_t index = 0; index < num_players; index++)
    {
        uint16_t id_player;
        new_game->get_number_of_players(id_player);
        Color color = new_game->add_new_player(id_player);
        users.push_back(UserLobbyInfo(id_player, color.get_text()));
    }
    games[id_counter] = new_game;
    return users;
}

void MonitorGames::set_session(const uint16_t &creator_id, const uint16_t &num_players, Socket &skt)
{

    games[id_counter]->set_session(skt, creator_id);
}

void MonitorGames::add_session(const uint16_t &session_id, const uint16_t &num_players, Socket &skt)
{
    std::lock_guard<std::mutex> lock(mtx);
    set_session(session_id, num_players, skt);
}

std::vector<UserLobbyInfo> MonitorGames::join_game(const uint16_t &game_id, const uint16_t &num_players)
{
    std::lock_guard<std::mutex> lock(mtx);
    std::vector<UserLobbyInfo> users;
    auto it = games.find(game_id);
    if (it == games.end())
        return users;
    std::cout << "Estoy aca" << std::endl;
    for (size_t index = 0; index < num_players; index++)
    {
        uint16_t id_player;
        it->second->get_number_of_players(id_player);
        std::cout << "El id es: " << (int)id_player << std::endl;
        Color color = it->second->add_new_player(id_player);
        std::cout << "El color elegido es: " << color.get_text() << std::endl;
        users.push_back(UserLobbyInfo(id_player, color.get_text()));
    }
    return users;
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