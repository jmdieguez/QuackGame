#include "lobby_session.h"
#include "protocol.h"

LobbySession::LobbySession(const uint16_t &i, Socket &skt, MonitorGames &m) : id(i), socket(std::move(skt)), matches(m)
{
}

LobbySession::~LobbySession() {}

void LobbySession::run() {
    ServerProtocol protocol(socket);
    std::vector<LobbyMessage> messages;
    while (_keep_running) {
        ActionLobby action = protocol.read_lobby();

        switch (action.type) {
            case ClientActionType::CREATE_GAME:
                game_joined = matches.create_game(id, action.game_name);
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
                if (game_joined != -1) {
                    matches.start_game(id, game_joined, socket);
                    _keep_running = false;
                }
                break;
            default:
                break;
        }
    }
}

void LobbySession::stop() {
    _keep_running = false;
    socket.shutdown(2);
    socket.close();
}