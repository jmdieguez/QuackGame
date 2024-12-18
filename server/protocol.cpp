
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
    uint16_t info;
    read_data(info);
    action = static_cast<ClientActionType>(info);

    uint16_t game_id = 0;
    if (action == ClientActionType::JOIN_GAME)
    {
        read_data(game_id);
        uint16_t num_players;
        read_data(num_players);
        return ActionLobby(action, game_id, num_players);
    }
    else if (action == ClientActionType::CREATE_GAME)
    {
        uint16_t num_players;
        read_data(num_players);
        std::string name = "";
        read_name(name);
        return ActionLobby(action, 0, num_players, name);
    }

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

void ServerProtocol::send_buffer(const std::vector<uint16_t>& buffer)
{
    bool was_closed = false;

    skt.sendall(buffer.data(), buffer.size() * sizeof(uint16_t), &was_closed);
    if (was_closed)
    {
        throw LibError(errno, "Error al intentar enviar buffer a cliente");
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

    std::vector<uint16_t> duck_poisitions;
    create_buffer_duck_positions(duck, duck_poisitions);
    send_buffer(duck_poisitions);

    std::vector<uint16_t> duck_status;
    create_buffer_duck_status(duck.status, duck_status);
    create_buffer_duck_status(duck.status, duck_status);
    send_buffer(duck_status);

    std::vector<uint16_t> colors;
    create_buffer_duck_color(duck.color, colors);
    send_buffer(colors);
}

void ServerProtocol::create_buffer_duck_positions(const DuckSnapshot &duck, std::vector<uint16_t> &buffer)
{
    buffer.clear();

    buffer.push_back(htons(static_cast<uint16_t>(duck.position.x)));
    buffer.push_back(htons(static_cast<uint16_t>(duck.position.y)));
    buffer.push_back(htons(static_cast<uint16_t>(duck.type_gun)));
    buffer.push_back(htons(static_cast<uint16_t>(duck.texture_gun)));
    buffer.push_back(htons(static_cast<uint16_t>(duck.position_gun.x)));
    buffer.push_back(htons(static_cast<uint16_t>(duck.position_gun.y)));
    buffer.push_back(htons(static_cast<uint16_t>(duck.angle_gun)));
}

void ServerProtocol::create_buffer_duck_status(const DuckStatus &status, std::vector<uint16_t> &buffer)
{
    buffer.clear();
    buffer.push_back(htons(static_cast<uint16_t>(status.mooving)));
    buffer.push_back(htons(static_cast<uint16_t>(status.shooting)));
    buffer.push_back(htons(static_cast<uint16_t>(status.jumping)));
    buffer.push_back(htons(static_cast<uint16_t>(status.start_jumping)));
    buffer.push_back(htons(static_cast<uint16_t>(status.falling)));
    buffer.push_back(htons(static_cast<uint16_t>(status.flapping)));
    buffer.push_back(htons(static_cast<uint16_t>(status.bent_down)));
    buffer.push_back(htons(static_cast<uint16_t>(status.grounded)));
    buffer.push_back(htons(static_cast<uint16_t>(status.looking_up)));
    buffer.push_back(htons(static_cast<uint16_t>(status.looking_right)));
    buffer.push_back(htons(static_cast<uint16_t>(status.has_helmet)));
    buffer.push_back(htons(static_cast<uint16_t>(status.has_chestplate)));
    buffer.push_back(htons(static_cast<uint16_t>(status.is_alive)));
    buffer.push_back(htons(static_cast<uint16_t>(status.gun_drop)));
    buffer.push_back(htons(static_cast<uint16_t>(status.gun_grab)));
    buffer.push_back(htons(static_cast<uint16_t>(status.banana_move)));
}

void ServerProtocol::create_buffer_duck_color(const Color& color, std::vector<uint16_t>& buffer)
{
    buffer.clear();
    buffer.push_back(htons(static_cast<uint16_t>(color.get_red())));
    buffer.push_back(htons(static_cast<uint16_t>(color.get_green())));
    buffer.push_back(htons(static_cast<uint16_t>(color.get_blue())));
}

void ServerProtocol::send_gun(const GunNoEquippedSnapshot &gun)
{
    std::vector<uint16_t> gun_buffer;
    create_buffer_gun(gun, gun_buffer);
    send_buffer(gun_buffer);
}

void ServerProtocol::create_buffer_gun(const GunNoEquippedSnapshot& gun, std::vector<uint16_t>& buffer)
{
    buffer.clear();
    buffer.push_back(htons(static_cast<uint16_t>(gun.texture)));
    buffer.push_back(htons(static_cast<uint16_t>(gun.position.x)));
    buffer.push_back(htons(static_cast<uint16_t>(gun.position.y)));
    buffer.push_back(htons(static_cast<uint16_t>(gun.angle)));
}


void ServerProtocol::send_projectile(const ProjectileSnapshot &projectile)
{
    std::vector<uint16_t> projectiles;
    create_buffer_projectile(projectile, projectiles);
    send_buffer(projectiles);
}

void ServerProtocol::create_buffer_projectile(const ProjectileSnapshot& projectile, std::vector<uint16_t>& buffer)
{
    buffer.clear();

    buffer.push_back(htons(static_cast<uint16_t>(projectile.id)));
    buffer.push_back(htons(static_cast<uint16_t>(projectile.type)));
    buffer.push_back(htons(static_cast<uint16_t>(projectile.texture)));
    buffer.push_back(htons(static_cast<uint16_t>(projectile.type_direction)));
    buffer.push_back(htons(static_cast<uint16_t>(projectile.pos_x)));
    buffer.push_back(htons(static_cast<uint16_t>(projectile.pos_y)));
}


void ServerProtocol::send_explosion(const ExplosionSnapshot &explosion)
{
    std::vector<uint16_t> explosions;
    create_buffer_explosion(explosion, explosions);
    send_buffer(explosions);
}

void ServerProtocol::create_buffer_explosion(const ExplosionSnapshot& explosion, std::vector<uint16_t>& buffer)
{
    buffer.clear();
    buffer.push_back(htons(static_cast<uint16_t>(explosion.id)));
    buffer.push_back(htons(static_cast<uint16_t>(explosion.texture)));
    buffer.push_back(htons(static_cast<uint16_t>(explosion.position.x)));
    buffer.push_back(htons(static_cast<uint16_t>(explosion.position.y)));
}


void ServerProtocol::send_box(const BoxSnapshot &box)
{
    std::vector<uint16_t> buffer;
    create_buffer_box(box, buffer);
    send_buffer(buffer);
}

void ServerProtocol::send_snapshot(const Snapshot &snapshot)
{
    send_data(snapshot.is_ended);
    if (snapshot.is_ended) {
        send_data(snapshot.winning_color.size());
        std::vector<unsigned char> name_color(snapshot.winning_color.begin(), snapshot.winning_color.end());
        send_name(name_color);
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
        send_data(score.color_name.length());
        send_name(std::vector<unsigned char>(score.color_name.begin(), score.color_name.end()));
    }
}

void ServerProtocol::create_buffer_map_component(const MapComponent &component, std::vector<uint16_t> &buffer) {
    buffer.clear();

    buffer.push_back(htons(static_cast<uint16_t>(component.type)));
    buffer.push_back(htons(static_cast<uint16_t>(component.x)));
    buffer.push_back(htons(static_cast<uint16_t>(component.y)));
}

void ServerProtocol::send_map_component(const MapComponent &component)
{
    std::vector<uint16_t> buffer;
    create_buffer_map_component(component, buffer);
    send_buffer(buffer);
}


void ServerProtocol::create_buffer_box(const BoxSnapshot &box, std::vector<uint16_t> &buffer) {
    buffer.clear();

    buffer.push_back(htons(static_cast<uint16_t>(box.pos.x)));
    buffer.push_back(htons(static_cast<uint16_t>(box.pos.y)));
    buffer.push_back(htons(static_cast<uint16_t>(box.status)));
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