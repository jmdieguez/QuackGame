#include "protocol.h"
#include <arpa/inet.h>
#include "../../common/liberror.h"
#include "../../common/snapshots.h"

ClientProtocol::ClientProtocol(Socket &skt) : skt(skt) {}

void ClientProtocol::read_snapshot(Snapshot &snapshot)
{
    uint16_t it;
    read_data(it);

    // std::cout << "La cantidad de patos son: " << (int)it << std::endl;
    for (uint16_t i = 0; i < it; i++)
    {
        uint16_t id;
        read_data(id);
        uint16_t pos_x;
        read_data(pos_x);
        uint16_t pos_y;
        read_data(pos_y);
        uint16_t current_action;
        read_data(current_action);
        uint16_t right_direction;   // Eliminar cuando se pueda enviar status al cliente
        read_data(right_direction); // Eliminar cuando se pueda enviar status al cliente
        bool is_right_direction = right_direction;
        PositionSnapshot p_snap(pos_x, pos_y);
        DuckAction action_value = static_cast<DuckAction>(current_action);
        DuckSnapshot duck(id, p_snap, action_value, is_right_direction);
        snapshot.ducks.emplace_back(duck);
    }
}

void ClientProtocol::read_data(uint16_t &data)
{
    bool was_closed = false;
    uint16_t data_received = 0;
    skt.recvall(&data_received, sizeof(uint16_t), &was_closed);
    if (was_closed)
    {
        throw LibError(errno, "Error al intentar recibir datos del servidor");
    }
    data = ntohs(data_received);
}

void ClientProtocol::send_action(const ClientActionType &action, bool &was_closed)
{
    uint16_t action_to_send = static_cast<uint16_t>(action);
    uint16_t data_converted = htons(action_to_send);
    skt.sendall(&data_converted, sizeof(data_converted), &was_closed);
}


void ClientProtocol::get_game_list(uint16_t& game_id, std::string& name) {
    uint16_t game_id_network_order;
    recv(&game_id_network_order, sizeof(game_id_network_order));
    game_id = ntohs(game_id_network_order);

    uint16_t nameLength_network_order;
    recv(&nameLength_network_order, sizeof(nameLength_network_order));
    uint16_t nameLength = ntohs(nameLength_network_order);

    std::vector<unsigned char> nameBytes(nameLength);
    recv(nameBytes.data(), nameLength);
    name.assign(nameBytes.begin(), nameBytes.end());
}

void ClientProtocol::recv(void* data, size_t size) {
    bool was_closed = false;
    skt.recvall(data, size, &was_closed);
    if (was_closed) {
        throw LibError(errno, "Error al intentar recibir datos del servidor");
    }
}

void ClientProtocol::send_create_game(const std::string& name) {
    bool was_closed = false;
    send_action(ClientActionType::CREATE_GAME, was_closed);
    if (was_closed) {
        throw LibError(errno, "Error al intentar enviar datos del servidor");
    }
    uint16_t length = static_cast<uint16_t>(name.size());
    uint16_t nameLength = htons(length);
    skt.sendall(&nameLength , sizeof(nameLength), &was_closed);

    std::vector<unsigned char> nameBytes(nameLength);
    send_name(nameBytes);

}

void ClientProtocol::send_name(const std::vector<unsigned char>& data) {
    bool was_closed = false;
    skt.sendall(data.data(), data.size(), &was_closed);
    if (was_closed) {
        throw LibError(errno, "Error al intentar enviar datos a cliente");
    }
}