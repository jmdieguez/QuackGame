#include "lobby_session.h"
#include "protocol.h"

LobbySession::LobbySession(const uint16_t &i, Socket &skt, MonitorGames &m) : id(i), socket(std::move(skt)), matches(m)
{
}

LobbySession::~LobbySession() {}

void LobbySession::run()
{
    ServerProtocol protocol(socket);
    std::vector<LobbyMessage> messages;
    std::vector<UserLobbyInfo> users;
    while (_keep_running)
    {
        ActionLobby action = protocol.read_lobby();
        switch (action.type)
        {
        case ClientActionType::CREATE_GAME:
            users = matches.create_game(id, action.game_name, action.num_players, socket);
            protocol.send_create_game_info(users);
            break;

        case ClientActionType::JOIN_GAME:
            matches.join_game(id, action.game_id, socket);
            game_joined = action.game_id;
            _keep_running = false;
            break;
        case ClientActionType::GAME_LIST:
            messages = matches.list_games();
            protocol.send_lobby_info(messages);
            break;
        case ClientActionType::START_GAME:
            uint16_t players;
            if (game_joined != -1)
            {
                matches.number_of_players(game_joined, players);
                if (players > 1)
                {
                    protocol.send_ready();
                    matches.start_game(id, game_joined);
                    _keep_running = false;
                }
                else
                {
                    protocol.send_not_ready();
                }
            }
            break;
        default:
            break;
        }
    }
}

void LobbySession::stop()
{
    _keep_running = false;
    socket.shutdown(2);
    socket.close();
}