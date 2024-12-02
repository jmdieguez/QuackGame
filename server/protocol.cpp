
#include "protocol.h"
#include "../common/liberror.h"
#include <arpa/inet.h>
#include <cstring>

ServerProtocol::ServerProtocol(Socket &socket) : skt(socket) {}

ActionMessage ServerProtocol::read_action()
{
    ClientActionType action;
    bool was_closed = false;

    uint16_t id;
    read_data(id);

    uint16_t info;
    skt.recvall(&info, sizeof(info), &was_closed);
    if (was_closed)
    {
        throw LibError(errno, "Error al intentar enviar datos a cliente");
    }
    action = static_cast<ClientActionType>(ntohs(info));
    return ActionMessage(id, action, "");
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
    if (action == ClientActionType::JOIN_GAME)
    {
        skt.recvall(&game_id, sizeof(game_id), &was_closed);
        if (was_closed)
        {
            throw LibError(errno, "Error al intentar enviar datos a cliente");
        }
        game_id = ntohs(game_id);
        uint16_t num_players;
        read_data(num_players);
        // return ActionLobby(action, game_id);
        return ActionLobby(action, game_id, num_players);
    }
    else if (action == ClientActionType::CREATE_GAME)
    {
        uint16_t num_players;
        read_data(num_players);
        std::string name = "";
        read_name(name);
        //   return ActionLobby(action, 0, name);
        return ActionLobby(action, 0, num_players, name);
    }

    //   return ActionLobby(action);
    return ActionLobby(action, game_id, game_id);
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

void ServerProtocol::read_data(uint16_t &data)
{
    bool was_closed = false;
    uint16_t info;
    skt.recvall(&info, sizeof(uint16_t), &was_closed);
    if (was_closed)
    {
        throw LibError(errno, "Error al intentar recibir datos del cliente");
    }
    data = ntohs(info);
}

void ServerProtocol::send_data_float(const float &data)
{
    bool was_closed = false;
    uint32_t info;

    std::memcpy(&info, &data, sizeof(float));
    info = htonl(info);

    skt.sendall(&info, sizeof(uint32_t), &was_closed);
    if (was_closed)
    {
        throw LibError(errno, "Error al intentar enviar datos al cliente");
    }
}

void ServerProtocol::send_duck(const DuckSnapshot &duck)
{
    send_data(duck.id);
    send_data(duck.position.x);
    send_data(duck.position.y);
    send_data(static_cast<uint16_t>(duck.type_gun));
    send_data(static_cast<uint16_t>(duck.texture_gun));
    send_data(static_cast<uint16_t>(duck.position_gun.x));
    send_data(static_cast<uint16_t>(duck.position_gun.y));
    send_data(static_cast<uint16_t>(duck.angle_gun));
    send_duck_status(duck.status);
    send_duck_color(duck.color);
}

void ServerProtocol::send_duck_color(Color color) {
    send_data(static_cast<uint16_t>(color.get_red()));
    send_data(static_cast<uint16_t>(color.get_green()));
    send_data(static_cast<uint16_t>(color.get_blue()));
}

void ServerProtocol::send_gun(const GunNoEquippedSnapshot &gun)
{
    send_data(static_cast<uint16_t>(gun.texture));
    send_data(static_cast<uint16_t>(gun.position.x));
    send_data(static_cast<uint16_t>(gun.position.y));
    send_data(static_cast<uint16_t>(gun.angle));
}

void ServerProtocol::send_projectile(const ProjectileSnapshot &projectile)
{
    send_data(static_cast<uint16_t>(projectile.id));
    send_data(static_cast<uint16_t>(projectile.type));
    send_data(static_cast<uint16_t>(projectile.texture));
    send_data(static_cast<uint16_t>(projectile.type_direction));
    send_data(static_cast<uint16_t>(projectile.pos_x));
    send_data(static_cast<uint16_t>(projectile.pos_y));
}

void ServerProtocol::send_explosion(const ExplosionSnapshot &explosion)
{
    send_data(static_cast<uint16_t>(explosion.id));
    send_data(static_cast<uint16_t>(explosion.texture));
    send_data(static_cast<uint16_t>(explosion.position.x));
    send_data(static_cast<uint16_t>(explosion.position.y));
}

void ServerProtocol::send_duck_status(const DuckStatus &status)
{
    send_data(static_cast<uint16_t>(status.mooving));
    send_data(static_cast<uint16_t>(status.shooting));
    send_data(static_cast<uint16_t>(status.jumping));
    send_data(static_cast<uint16_t>(status.start_jumping));
    send_data(static_cast<uint16_t>(status.falling));
    send_data(static_cast<uint16_t>(status.flapping));
    send_data(static_cast<uint16_t>(status.bent_down));
    send_data(static_cast<uint16_t>(status.grounded));
    send_data(static_cast<uint16_t>(status.looking_up));
    send_data(static_cast<uint16_t>(status.looking_right));
    send_data(static_cast<uint16_t>(status.has_helmet));
    send_data(static_cast<uint16_t>(status.has_chestplate));
    send_data(static_cast<uint16_t>(status.is_alive));
    send_data(static_cast<uint16_t>(status.gun_drop));
    send_data(static_cast<uint16_t>(status.gun_grab));
    send_data(static_cast<uint16_t>(status.banana_move));
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
    send_data(snapshot.is_ended);
    if (snapshot.is_ended) {
        send_data(static_cast<uint16_t>(snapshot.game_result));
    }
    send_data(static_cast<uint16_t>(snapshot.round));
    const uint16_t ducks_length = static_cast<uint16_t>(snapshot.ducks.size());
    send_data(ducks_length);
    for (const DuckSnapshot &duck : snapshot.ducks)
        send_duck(duck);
    const uint16_t guns_length = static_cast<uint16_t>(snapshot.guns.size());
    send_data(guns_length);
    for (const GunNoEquippedSnapshot &gun : snapshot.guns)
        send_gun(gun);
    const uint16_t projectile_length = static_cast<uint16_t>(snapshot.projectiles.size());
    send_data(projectile_length);
    for (const ProjectileSnapshot &projectile : snapshot.projectiles)
        send_projectile(projectile);

    const uint16_t explosion_length = static_cast<uint16_t>(snapshot.explosions.size());
    send_data(explosion_length);

    for (const ExplosionSnapshot &explosion : snapshot.explosions)
        send_explosion(explosion);

    send_data(snapshot.map.style);
    send_data(snapshot.map.size_x);
    send_data(snapshot.map.size_y);
    const uint16_t components_length = static_cast<uint16_t>(snapshot.map.components.size());
    send_data(components_length);
    for (const MapComponent &component : snapshot.map.components)
        send_map_component(component);

    const uint16_t boxes_length = static_cast<uint16_t>(snapshot.boxes.size());
    send_data(boxes_length);
    for (const BoxSnapshot &box : snapshot.boxes)
        send_box(box);

    send_data(snapshot.map.gun_spawns.size());
    for (const Position &position : snapshot.map.gun_spawns)
    {
        send_data(position.x);
        send_data(position.y);
    }
    send_data(static_cast<uint16_t>(snapshot.camera.x));
    send_data(static_cast<uint16_t>(snapshot.camera.y));
    send_data(static_cast<uint16_t>(snapshot.camera.width));
    send_data(static_cast<uint16_t>(snapshot.camera.height));

    const uint16_t armors_length = static_cast<uint16_t>(snapshot.armors.size());
    send_data(armors_length);
    for (const ArmorSnapshot &armor : snapshot.armors)
    {
        send_data(armor.position.x);
        send_data(armor.position.y);
        send_data(static_cast<int>(armor.type));
    }

    const uint16_t scores_size = static_cast<uint16_t>(snapshot.scores.size());
    send_data(scores_size);
    for (const DuckScore &score : snapshot.scores)
    {
        send_data(score.victories);
        send_duck_color(score.color);
    }
}

void ServerProtocol::send_lobby_info(const std::vector<LobbyMessage> &lobby_info)
{

    send_data(static_cast<uint16_t>(ClientActionType::GAME_LIST));
    uint16_t size = lobby_info.size();
    send_data(size);

    for (const auto &msg : lobby_info)
    {
        send_data(msg.game_id);
        send_data(msg.name.length());
        send_name(std::vector<unsigned char>(msg.name.begin(), msg.name.end()));
    }
}

void ServerProtocol::send_users(std::vector<UserLobbyInfo> &users)
{
    const uint16_t users_length = static_cast<uint16_t>(users.size());
    send_data(users_length);
    for (UserLobbyInfo &user : users)
    {
        std::string color = user.get_color();
        send_data(user.get_id());
        send_data(color.size());
        std::vector<unsigned char> name_color(color.begin(), color.end());
        send_name(name_color);
    }
}

void ServerProtocol::send_join_game_info(std::vector<UserLobbyInfo> &users)
{
    const uint16_t users_length = static_cast<uint16_t>(users.size());
    send_data(users_length);
    for (UserLobbyInfo &user : users)
    {
        std::string color = user.get_color();
        send_data(user.get_id());
        send_data(user.get_color().size());
        std::vector<unsigned char> name_color(user.get_color().begin(), user.get_color().end());
        send_name(name_color);
    }
}

void ServerProtocol::send_name(const std::vector<unsigned char> &data)
{
    bool was_closed = false;
    skt.sendall(data.data(), data.size(), &was_closed);
    if (was_closed)
    {
        throw LibError(errno, "Error al intentar enviar datos a cliente");
    }
}

void ServerProtocol::read_name(std::string &name)
{
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
    name.assign(nameBuffer.begin(), nameBuffer.end());
}

void ServerProtocol::send_not_ready()
{
    send_data(static_cast<uint16_t>(ClientActionType::NOT_READY));
}

void ServerProtocol::send_ready()
{
    send_data(static_cast<uint16_t>(ClientActionType::READY));
}