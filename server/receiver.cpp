#include "receiver.h"
#include "protocol.h"
#include "../common/liberror.h"
#include "client_command.h"

Receiver::Receiver(Socket &skt, const uint16_t &id, GamesManager& game_manager, Queue<Snapshot>& queue,
                   Queue<LobbyMessage>& l,  std::atomic<bool>& playing):
    session_id(id), client(skt), sender_queue(queue), lobby_queue(l), protocol(skt), closed(false),
    game_manager(game_manager), is_playing(playing) {}

Receiver::~Receiver() {}

void Receiver::run()
{
    try
    {
        while (!closed && _keep_running)
        {
            if (!is_playing) {
                ActionLobby message = protocol.read_lobby();
                game_queue = game_manager.handle_lobby(message, session_id, lobby_queue);
            } else {
                if (!closed) {
                    ActionMessage message = protocol.read_action();
                    ClientCommand command(session_id, message);
                    game_queue->push(command);
                }
            }
        }
    }
    catch (LibError &e)
    {
    }
    catch (ClosedQueue &e)
    {
    }
    _is_alive = false;
}
