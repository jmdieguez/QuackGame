#include "protocol.h"
#include <arpa/inet.h>
#include "../../common/liberror.h"
#include "../../common/snapshots.h"

ClientProtocol::ClientProtocol(Socket &skt) : skt(skt) {}

void ClientProtocol::read_snapshot(Snapshot &snapshot)
{
    uint16_t duck_lenght;
    read_data(duck_lenght);
    for (uint16_t i = 0; i < duck_lenght; i++)
    {
        uint16_t id;
        read_data(id);
        uint16_t pos_x;
        read_data(pos_x);
        uint16_t pos_y;
        read_data(pos_y);
        uint16_t current_action;
        read_data(current_action);
        uint16_t current_gun;
        read_data(current_gun);
        uint16_t right_direction;   // Eliminar cuando se pueda enviar status al cliente
        read_data(right_direction); // Eliminar cuando se pueda enviar status al cliente
        bool is_right_direction = right_direction;
        PositionSnapshot p_snap(pos_x, pos_y);
        DuckAction action_value = static_cast<DuckAction>(current_action);
        GunType gun_value = static_cast<GunType>(current_gun);
        DuckSnapshot duck(id, p_snap, action_value, gun_value, is_right_direction);
        snapshot.ducks.emplace_back(duck);
    }
    uint16_t guns_lenght;
    read_data(guns_lenght);

    for (uint16_t i = 0; i < guns_lenght; i++)
    {
        uint16_t type;
        read_data(type);
        uint16_t pos_x;
        read_data(pos_x);
        uint16_t pos_y;
        read_data(pos_y);
        GunType type_value = static_cast<GunType>(type);
        GunNoEquippedSnapshot gun(type_value, pos_x, pos_y);
        snapshot.guns.emplace_back(gun);
    }
}

void ClientProtocol::read_data(uint16_t &data)
{
    bool was_closed = false;
    uint16_t data_received = 0;
    skt.recvall(&data_received, sizeof(uint16_t), &was_closed);
    if (was_closed)
    {
        throw LibError(errno, "Error al intentar enviar datos a cliente");
    }
    data = ntohs(data_received);
}

void ClientProtocol::send_action(const ClientActionType &action, bool &was_closed)
{
    uint16_t action_to_send = static_cast<uint16_t>(action);
    uint16_t data_converted = htons(action_to_send);
    skt.sendall(&data_converted, sizeof(data_converted), &was_closed);
}
