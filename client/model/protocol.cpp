#include "protocol.h"
#include <arpa/inet.h>
#include <cstring>
#include "../../common/liberror.h"
#include "../../common/snapshots.h"
#include "../../common/map.h"

DuckStatus ClientProtocol::read_status()

{
    uint16_t mooving;
    read_data(mooving);
    uint16_t shooting;
    read_data(shooting);
    uint16_t jumping;
    read_data(jumping);
    uint16_t start_jumping;
    read_data(start_jumping);
    uint16_t falling;
    read_data(falling);
    uint16_t flapping;
    read_data(flapping);
    uint16_t bent_down;
    read_data(bent_down);
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
    DuckStatus duck_status = {!!mooving, !!shooting, !!jumping, !!start_jumping, !!falling, !!flapping, !!bent_down, !!grounded, !!looking_up, !!looking_right, !!has_helmet, !!has_chestplate, !!is_alive};
    return duck_status;
}

ProjectileSnapshot ClientProtocol::read_projectile()
{
    uint16_t type;
    read_data(type);
    uint16_t texture;
    read_data(texture);
    uint16_t type_direction;
    read_data(type_direction);
    uint16_t pos_x;
    read_data(pos_x);
    uint16_t pos_y;
    read_data(pos_y);
    uint16_t finish;
    read_data(finish);
    ProjectileType type_value = static_cast<ProjectileType>(type);
    TextureFigure texture_value = static_cast<TextureFigure>(texture);
    ProjectileDirection type_direction_value = static_cast<ProjectileDirection>(type_direction);
    ProjectileSnapshot projectile(pos_x, pos_y, type_value, texture_value, type_direction_value, !!finish);
    return projectile;
}

ClientProtocol::ClientProtocol(Socket &skt) : skt(skt) {}

void ClientProtocol::read_snapshot(Snapshot &snapshot)
{
    uint16_t duck_length;
    read_data(duck_length);
    for (uint16_t i = 0; i < duck_length; i++)
    {
        uint16_t id;
        read_data(id);
        uint16_t x;
        read_data(x);
        uint16_t y;
        read_data(y);
        uint16_t duck_width;
        read_data(duck_width);
        uint16_t duck_height;
        read_data(duck_height);
        uint16_t type_gun;
        read_data(type_gun);
        uint16_t texture_gun;
        read_data(texture_gun);
        uint16_t gun_width;
        read_data(gun_width);
        uint16_t gun_height;
        read_data(gun_height);
        uint16_t gun_x;
        read_data(gun_x);
        uint16_t gun_y;
        read_data(gun_y);
        uint16_t gun_angle;
        read_data(gun_angle);
        DuckStatus duck_status = read_status();
        Position p(x, y);
        Size duck_size(duck_width, duck_height);
        GunType type_gun_value = static_cast<GunType>(type_gun);
        TextureFigure texture_gun_value = static_cast<TextureFigure>(texture_gun);
        Size gun_size(gun_width, gun_height);
        Position gun_position(gun_x, gun_y);
        DuckSnapshot duck(id, p, duck_size, type_gun_value, texture_gun_value, gun_size, gun_position, gun_angle, duck_status);
        snapshot.ducks.emplace_back(duck);
    }
    uint16_t guns_length;
    read_data(guns_length);

    for (uint16_t i = 0; i < guns_length; i++)
    {
        uint16_t texture;
        read_data(texture);
        uint16_t x;
        read_data(x);
        uint16_t y;
        read_data(y);
        TextureFigure texture_value = static_cast<TextureFigure>(texture);
        uint16_t weigth;
        read_data(weigth);
        uint16_t height;
        read_data(height);
        uint16_t angle;
        read_data(angle);
        GunNoEquippedSnapshot gun(texture_value, Position(x, y), Size(weigth, height), angle);
        snapshot.guns.emplace_back(gun);
    }

    uint16_t projectile_length;
    read_data(projectile_length);

    for (uint16_t i = 0; i < projectile_length; i++)
    {
        ProjectileSnapshot projectile = read_projectile();
        snapshot.projectiles.emplace_back(projectile);
    }

    uint16_t sound_lenght;
    read_data(sound_lenght);
    for (uint16_t i = 0; i < sound_lenght; i++)
    {
        uint16_t sound_type;
        read_data(sound_type);
        SoundType type_value = static_cast<SoundType>(sound_type);
        snapshot.sounds.emplace_back(type_value);
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

    uint16_t boxes_length;
    read_data(boxes_length);
    for (uint16_t i = 0; i < boxes_length; i++)
    {
        uint16_t x, y, box_status;
        read_data(x);
        read_data(y);
        read_data(box_status);
        Position pos(x, y);
        snapshot.map.boxes.push_back(BoxSnapshot(pos, static_cast<Box>(box_status)));
    }

    uint16_t gun_spawns;
    read_data(gun_spawns);
    for (uint16_t i = 0; i < gun_spawns; i++)
    {
        uint16_t x, y;
        read_data(x);
        read_data(y);
        snapshot.map.gun_spawns.push_back(Position(x, y));
    }
    float numero;
    read_data_float(numero);
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

void ClientProtocol::read_data_float(float &data)
{
    bool was_closed = false;
    uint32_t data_received = 0;

    skt.recvall(&data_received, sizeof(uint32_t), &was_closed);
    if (was_closed)
    {
        throw LibError(errno, "Error al intentar recibir datos del cliente");
    }

    data_received = ntohl(data_received);
    std::memcpy(&data, &data_received, sizeof(float));
}

void ClientProtocol::send_action(const ClientActionType &action, bool &was_closed)
{
    uint16_t action_to_send = static_cast<uint16_t>(action);
    uint16_t data_converted = htons(action_to_send);
    skt.sendall(&data_converted, sizeof(data_converted), &was_closed);
}

void ClientProtocol::get_game_list(uint16_t &game_id, std::string &name)
{
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

void ClientProtocol::recv(void *data, size_t size)
{
    bool was_closed = false;
    skt.recvall(data, size, &was_closed);
    if (was_closed)
    {
        throw LibError(errno, "Error al intentar recibir datos del servidor");
    }
}

void ClientProtocol::send_create_game(const std::string &name)
{
    bool was_closed = false;
    send_action(ClientActionType::CREATE_GAME, was_closed);
    if (was_closed)
    {
        throw LibError(errno, "Error al intentar enviar datos del servidor");
    }

    uint16_t length = static_cast<uint16_t>(name.size());
    uint16_t nameLength = htons(length);
    skt.sendall(&nameLength, sizeof(nameLength), &was_closed);
    if (was_closed)
    {
        throw LibError(errno, "Error al intentar enviar datos del servidor");
    }

    std::vector<unsigned char> nameBytes(name.begin(), name.end());
    send_name(nameBytes);
}

void ClientProtocol::send_name(const std::vector<unsigned char> &data)
{
    bool was_closed = false;
    skt.sendall(data.data(), data.size(), &was_closed);
    if (was_closed)
    {
        throw LibError(errno, "Error al intentar enviar datos a cliente");
    }
}

void ClientProtocol::send_join_game(const uint16_t &id)
{
    bool was_closed = false;
    send_action(ClientActionType::JOIN_GAME, was_closed);
    if (was_closed)
    {
        throw LibError(errno, "Error al intentar enviar datos a cliente");
    }
    uint16_t id_converted = htons(id);
    skt.sendall(&id_converted, sizeof(uint16_t), &was_closed);
    if (was_closed)
    {
        throw LibError(errno, "Error al intentar enviar datos del servidor");
    }
}

void ClientProtocol::send_start_game()
{
    bool was_closed = false;
    send_action(ClientActionType::START_GAME, was_closed);
    if (was_closed)
    {
        throw LibError(errno, "Error al intentar enviar datos del servidor");
    }
}

void ClientProtocol::read_list(std::map<uint16_t, std::string> &games)
{
    uint16_t action;
    read_data(action);
    if (action != static_cast<uint16_t>(ClientActionType::GAME_LIST))
    {
        std::cerr << "Error: Tipo de acción no esperado" << std::endl;
        return;
    }

    uint16_t size;
    read_data(size);

    for (uint16_t i = 0; i < size; i++)
    {
        uint16_t game_id;
        read_data(game_id);
        bool was_closed = false;
        uint16_t nameLength;
        skt.recvall(reinterpret_cast<char *>(&nameLength), sizeof(nameLength), &was_closed);
        if (was_closed)
        {
            throw LibError(errno, "Error al intentar leer datos a cliente");
        }

        uint16_t length = ntohs(nameLength);
        std::vector<char> nameBuffer(length);
        skt.recvall(nameBuffer.data(), length, &was_closed);
        if (was_closed)
        {
            throw LibError(errno, "Error al intentar leer datos a cliente");
        }
        std::string name;
        name.assign(nameBuffer.begin(), nameBuffer.end());
        games[game_id] = name;
    }
}

void ClientProtocol::send_game_list()
{
    bool was_closed = false;
    send_action(ClientActionType::GAME_LIST, was_closed);
    if (was_closed)
    {
        throw LibError(errno, "Error al intentar enviar datos a cliente");
    }
}
