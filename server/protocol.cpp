
#include "protocol.h"
#include "../common/liberror.h"
#include <arpa/inet.h>

ServerProtocol::ServerProtocol(Socket &socket) : skt(socket) {}

ActionMessage ServerProtocol::read_action()
{
    ClientActionType action;
    bool was_closed = false;

    uint16_t info;
    skt.recvall(&info, sizeof(info), &was_closed);
    if (was_closed)
    {
        throw LibError(errno, "Error al intentar enviar datos a cliente");
    }
    action = static_cast<ClientActionType>(ntohs(info));
    return ActionMessage(action, "");
}

ActionLobby ServerProtocol::read_lobby()
{
    ClientActionType action;
    bool was_closed = false;

    uint16_t info;
    skt.recvall(&info, sizeof(info), &was_closed);
    if (was_closed)
    {
        throw LibError(errno, "Error al intentar enviar datos a cliente");
    }
    action = static_cast<ClientActionType>(ntohs(info));
    uint16_t game_id = 0;
    if (action == ClientActionType::START_GAME || action == ClientActionType::JOIN_GAME) {
        skt.recvall(&game_id, sizeof(game_id), &was_closed);
        if (was_closed)
        {
            throw LibError(errno, "Error al intentar enviar datos a cliente");
        }
        game_id = ntohs(game_id);
        return ActionLobby(action, game_id);
    } else if (action == ClientActionType::CREATE_GAME) {
        std::string name = "";
        read_name(name);
        return ActionLobby(action, 0, name);
    }
    return ActionLobby(action);
}

void ServerProtocol::send_data(const uint16_t &data)
{
    bool was_closed = false;
    uint16_t info = htons(data);
    skt.sendall(&info, sizeof(uint16_t), &was_closed);
    if (was_closed)
    {
        throw LibError(errno, "Error al intentar enviar datos a cliente");
    }
}

void ServerProtocol::send_duck(const DuckSnapshot &duck)
{
    send_data(duck.id);
    send_data(duck.position.x);
    send_data(duck.position.y);
    send_data(static_cast<uint16_t>(duck.current_action));
    send_data(static_cast<uint16_t>(duck.size_duck.width));
    send_data(static_cast<uint16_t>(duck.size_duck.height));
    send_data(static_cast<uint16_t>(duck.gun));
    send_data(static_cast<uint16_t>(duck.size_gun.width));
    send_data(static_cast<uint16_t>(duck.size_gun.height));
    send_data(static_cast<uint16_t>(duck.position_gun.x));
    send_data(static_cast<uint16_t>(duck.position_gun.y));
    send_data(static_cast<uint16_t>(duck.angle_gun));
    send_duck_status(duck.status);
}

void ServerProtocol::send_gun(const GunNoEquippedSnapshot &gun)
{
    send_data(static_cast<uint16_t>(gun.type));
    send_data(static_cast<uint16_t>(gun.position.x));
    send_data(static_cast<uint16_t>(gun.position.y));
    send_data(static_cast<uint16_t>(gun.size.width));
    send_data(static_cast<uint16_t>(gun.size.height));
    send_data(static_cast<uint16_t>(gun.angle));
}

void ServerProtocol::send_projectile(const ProjectileSnapshot &projectile)
{
    send_data(static_cast<uint16_t>(projectile.type));
    send_data(static_cast<uint16_t>(projectile.type_direction));
    send_data(static_cast<uint16_t>(projectile.pos_x));
    send_data(static_cast<uint16_t>(projectile.pos_y));
    send_data(static_cast<uint16_t>(projectile.finish));
}

void ServerProtocol::send_duck_status(const DuckStatus &status)
{
    send_data(static_cast<uint16_t>(status.shooting));
    send_data(static_cast<uint16_t>(status.jumping));
    send_data(static_cast<uint16_t>(status.bent_down));
    send_data(static_cast<uint16_t>(status.grounded));
    send_data(static_cast<uint16_t>(status.looking_up));
    send_data(static_cast<uint16_t>(status.looking_right));
    send_data(static_cast<uint16_t>(status.has_helmet));
    send_data(static_cast<uint16_t>(status.has_chestplate));
    send_data(static_cast<uint16_t>(status.is_alive));
}

void ServerProtocol::send_map_component(const MapComponent &component)
{
    send_data(static_cast<uint16_t>(component.type));
    send_data(component.x);
    send_data(component.y);
}

void ServerProtocol::send_box(const BoxSnapshot &box)
{
    send_data(box.pos.x);
    send_data(box.pos.y);
    send_data(static_cast<uint16_t>(box.status));
}

void ServerProtocol::send_snapshot(const Snapshot &snapshot)
{
    const uint16_t ducks_lenght = static_cast<uint16_t>(snapshot.ducks.size());
    send_data(ducks_lenght);
    for (const DuckSnapshot &duck : snapshot.ducks)
        send_duck(duck);
    const uint16_t guns_lenght = static_cast<uint16_t>(snapshot.guns.size());
    send_data(guns_lenght);
    for (const GunNoEquippedSnapshot &gun : snapshot.guns)
        send_gun(gun);
    const uint16_t projectile_lenght = static_cast<uint16_t>(snapshot.projectiles.size());
    send_data(projectile_lenght);
    for (const ProjectileSnapshot &projectile : snapshot.projectiles)
        send_projectile(projectile);

    send_data(snapshot.map.style);
    send_data(snapshot.map.size_x);
    send_data(snapshot.map.size_y);
    const uint16_t components_length = static_cast<uint16_t>(snapshot.map.components.size());
    send_data(components_length);
    for (const MapComponent &component : snapshot.map.components)
        send_map_component(component);

    const uint16_t boxes_length = static_cast<uint16_t>(snapshot.map.boxes.size());
    send_data(boxes_length);
    for (const BoxSnapshot &box : snapshot.map.boxes)
        send_box(box);
}

void ServerProtocol::send_lobby_info(const LobbyMessage& lobby) {
    send_data(lobby.game_id);

    uint16_t nameLength = static_cast<uint16_t>(lobby.name.length());
    send_data(nameLength);

    std::vector<unsigned char> nameBytes(lobby.name.begin(), lobby.name.end());
    send_name(nameBytes);
}

void ServerProtocol::send_name(const std::vector<unsigned char>& data) {
    bool was_closed = false;
    skt.sendall(data.data(), data.size(), &was_closed);
    if (was_closed) {
        throw LibError(errno, "Error al intentar enviar datos a cliente");
    }
}

void ServerProtocol::read_name(std::string& name) {
    bool was_closed = false;
    uint16_t nameLength;
    skt.recvall(reinterpret_cast<char*>(&nameLength), sizeof(nameLength), &was_closed);
    if (was_closed) {
        throw LibError(errno, "Error al intentar leer datos a cliente");
    }

    uint16_t length = ntohs(nameLength);
    std::vector<char> nameBuffer(length);
    skt.recvall(nameBuffer.data(), length, &was_closed);
    if (was_closed) {
        throw LibError(errno, "Error al intentar leer datos a cliente");
    }
    name.assign(nameBuffer.begin(), nameBuffer.end());
}