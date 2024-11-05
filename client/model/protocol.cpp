#include "protocol.h"
#include <arpa/inet.h>
#include "../../common/liberror.h"
#include "../../common/snapshots.h"
#include "../../common/map.h"

DuckStatus ClientProtocol::read_status()
{
    uint16_t shooting;
    read_data(shooting);
    uint16_t jumping;
    read_data(jumping);
    uint16_t grounded;
    read_data(grounded);
    uint16_t looking_up;
    read_data(looking_up);
    uint16_t looking_right;
    read_data(looking_right);
    uint16_t has_helmet;
    read_data(has_helmet);
    uint16_t has_chestplate;
    read_data(has_chestplate);
    uint16_t is_alive;
    read_data(is_alive);
    DuckStatus duck_status = {!!shooting, !!jumping, !!grounded, !!looking_up, !!looking_right, !!has_helmet, !!has_chestplate, !!is_alive};
    return duck_status;
}

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
        DuckStatus duck_status = read_status();
        PositionSnapshot p_snap(pos_x, pos_y);
        DuckAction action_value = static_cast<DuckAction>(current_action);
        GunType gun_value = static_cast<GunType>(current_gun);
        DuckSnapshot duck(id, p_snap, action_value, gun_value, duck_status);
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

    uint16_t style, size_x, size_y, components_length;
    read_data(style);
    read_data(size_x);
    read_data(size_y);
    read_data(components_length);

    snapshot.map.style = style;
    snapshot.map.size_x = size_x;
    snapshot.map.size_y = size_y;

    for (uint16_t i = 0; i < components_length; i++)
    {
        uint16_t type, x, y;
        read_data(type);
        read_data(x);
        read_data(y);
        Component aux = static_cast<Component>(type);
        MapComponent component(x, y, aux);
        snapshot.map.components.emplace_back(component);
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
