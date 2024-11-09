
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
    send_data(static_cast<uint16_t>(duck.gun));
    send_data(static_cast<uint16_t>(duck.size_gun.width));
    send_data(static_cast<uint16_t>(duck.size_gun.height));
    send_duck_status(duck.status);
}

void ServerProtocol::send_gun(const GunNoEquippedSnapshot &gun)
{
    send_data(static_cast<uint16_t>(gun.type));
    send_data(static_cast<uint16_t>(gun.position.x));
    send_data(static_cast<uint16_t>(gun.position.y));
    send_data(static_cast<uint16_t>(gun.size.width));
    send_data(static_cast<uint16_t>(gun.size.height));
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
}
