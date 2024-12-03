
#include <gtest/gtest.h>
#include "mock/mock_socket.h"
#include "../server/protocol.h"
#include <gmock/gmock.h>
#include <arpa/inet.h>


using ::testing::DoAll;
using ::testing::Return;


TEST(ServerProtocolTest, TestDuckStatusBuffer) {
    MockSocket mock_socket("9999");
    ServerProtocol protocol(mock_socket);

    // Crear un objeto DuckStatus con datos de ejemplo
    DuckStatus status;
    status.mooving = 1;
    status.shooting = 0;
    status.jumping = 1;
    status.start_jumping = 0;
    status.falling = 0;
    status.flapping = 1;
    status.bent_down = 0;
    status.grounded = 1;
    status.looking_up = 0;
    status.looking_right = 1;
    status.has_helmet = 1;
    status.has_chestplate = 0;
    status.is_alive = 1;
    status.gun_drop = 0;
    status.gun_grab = 1;
    status.banana_move = 0;

    // Crear un buffer vacío
    std::vector<uint16_t> buffer;

    protocol.create_buffer_duck_status(status, buffer);

    EXPECT_EQ(buffer.size(), 16); // Debería tener 16 elementos (uno por cada campo serializado)

    EXPECT_EQ(buffer[0], static_cast<uint16_t>(htons(static_cast<uint16_t>(status.mooving))));
    EXPECT_EQ(buffer[1], static_cast<uint16_t>(htons(static_cast<uint16_t>(status.shooting))));
    EXPECT_EQ(buffer[2], static_cast<uint16_t>(htons(static_cast<uint16_t>(status.jumping))));
    EXPECT_EQ(buffer[3], static_cast<uint16_t>(htons(static_cast<uint16_t>(status.start_jumping))));
    EXPECT_EQ(buffer[4], static_cast<uint16_t>(htons(static_cast<uint16_t>(status.falling))));
    EXPECT_EQ(buffer[5], static_cast<uint16_t>(htons(static_cast<uint16_t>(status.flapping))));
    EXPECT_EQ(buffer[6], static_cast<uint16_t>(htons(static_cast<uint16_t>(status.bent_down))));
    EXPECT_EQ(buffer[7], static_cast<uint16_t>(htons(static_cast<uint16_t>(status.grounded))));
    EXPECT_EQ(buffer[8], static_cast<uint16_t>(htons(static_cast<uint16_t>(status.looking_up))));
    EXPECT_EQ(buffer[9], static_cast<uint16_t>(htons(static_cast<uint16_t>(status.looking_right))));
    EXPECT_EQ(buffer[10], static_cast<uint16_t>(htons(static_cast<uint16_t>(status.has_helmet))));
    EXPECT_EQ(buffer[11], static_cast<uint16_t>(htons(static_cast<uint16_t>(status.has_chestplate))));
    EXPECT_EQ(buffer[12], static_cast<uint16_t>(htons(static_cast<uint16_t>(status.is_alive))));
    EXPECT_EQ(buffer[13], static_cast<uint16_t>(htons(static_cast<uint16_t>(status.gun_drop))));
    EXPECT_EQ(buffer[14], static_cast<uint16_t>(htons(static_cast<uint16_t>(status.gun_grab))));
    EXPECT_EQ(buffer[15], static_cast<uint16_t>(htons(static_cast<uint16_t>(status.banana_move))));
}

TEST(ServerProtocolTest, TestDuckPositionsBuffer) {
    MockSocket mock_socket("9999");
    ServerProtocol protocol(mock_socket);

    // Crear un objeto DuckSnapshot con datos de ejemplo
    DuckSnapshot duck(42, Position(10, 20), GunType::Shotgun, TextureFigure::ShotgunFigure, Position(30, 40), 45,
                      DuckStatus(),
                      Color());

    std::vector<uint16_t> buffer;

    protocol.create_buffer_duck_positions(duck, buffer);

    EXPECT_EQ(buffer.size(), 7); // Debería tener 7 elementos (uno por cada campo serializado)

    EXPECT_EQ(buffer[0], static_cast<uint16_t>(htons(static_cast<uint16_t>(duck.position.x))));
    EXPECT_EQ(buffer[1], static_cast<uint16_t>(htons(static_cast<uint16_t>(duck.position.y))));
    EXPECT_EQ(buffer[2], static_cast<uint16_t>(htons(static_cast<uint16_t>(duck.type_gun))));
    EXPECT_EQ(buffer[3], static_cast<uint16_t>(htons(static_cast<uint16_t>(duck.texture_gun))));
    EXPECT_EQ(buffer[4], static_cast<uint16_t>(htons(static_cast<uint16_t>(duck.position_gun.x))));
    EXPECT_EQ(buffer[5], static_cast<uint16_t>(htons(static_cast<uint16_t>(duck.position_gun.y))));
    EXPECT_EQ(buffer[6], static_cast<uint16_t>(htons(static_cast<uint16_t>(duck.angle_gun))));
}

TEST(ServerProtocolTest, TestDuckColorBuffer) {
    MockSocket mock_socket("9999");
    ServerProtocol protocol(mock_socket);

    Color color(100, 150, 200);

    std::vector<uint16_t> buffer;

    protocol.create_buffer_duck_color(color, buffer);

    EXPECT_EQ(buffer.size(), 3); // Debería tener 3 elementos (uno por cada componente de color)

    EXPECT_EQ(buffer[0], static_cast<uint16_t>(htons(static_cast<uint16_t>(color.get_red()))));
    EXPECT_EQ(buffer[1], static_cast<uint16_t>(htons(static_cast<uint16_t>(color.get_green()))));
    EXPECT_EQ(buffer[2], static_cast<uint16_t>(htons(static_cast<uint16_t>(color.get_blue()))));
}

TEST(ServerProtocolTest, TestGunBuffer) {
    MockSocket mock_socket("9999");
    ServerProtocol protocol(mock_socket);

    GunNoEquippedSnapshot gun(TextureFigure::CowboyPistolFigure, Position(20, 30), 45);

    std::vector<uint16_t> buffer;

    protocol.create_buffer_gun(gun, buffer);

    EXPECT_EQ(buffer.size(), 4); // Debería tener 4 elementos (uno por cada campo serializado)

    EXPECT_EQ(buffer[0], static_cast<uint16_t>(htons(static_cast<uint16_t>(gun.texture))));
    EXPECT_EQ(buffer[1], static_cast<uint16_t>(htons(static_cast<uint16_t>(gun.position.x))));
    EXPECT_EQ(buffer[2], static_cast<uint16_t>(htons(static_cast<uint16_t>(gun.position.y))));
    EXPECT_EQ(buffer[3], static_cast<uint16_t>(htons(static_cast<uint16_t>(gun.angle))));
}


TEST(ServerProtocolTest, TestProjectileBuffer) {
    MockSocket mock_socket("9999");
    ServerProtocol protocol(mock_socket);

    ProjectileSnapshot projectile(1, 2,3, ProjectileType::ChainBullet, TextureFigure::CowboyBullet, ProjectileDirection::Right);

    std::vector<uint16_t> buffer;
    protocol.create_buffer_projectile(projectile, buffer);

    EXPECT_EQ(buffer.size(), 6);

    EXPECT_EQ(buffer[0], static_cast<uint16_t>(htons(static_cast<uint16_t>(projectile.id))));
    EXPECT_EQ(buffer[1], static_cast<uint16_t>(htons(static_cast<uint16_t>(projectile.type))));
    EXPECT_EQ(buffer[2], static_cast<uint16_t>(htons(static_cast<uint16_t>(projectile.texture))));
    EXPECT_EQ(buffer[3], static_cast<uint16_t>(htons(static_cast<uint16_t>(projectile.type_direction))));
    EXPECT_EQ(buffer[4], static_cast<uint16_t>(htons(static_cast<uint16_t>(projectile.pos_x))));
    EXPECT_EQ(buffer[5], static_cast<uint16_t>(htons(static_cast<uint16_t>(projectile.pos_y))));
}

TEST(ServerProtocolTest, TestExplosionBuffer) {
    MockSocket mock_socket("9999");
    ServerProtocol protocol(mock_socket);

    ExplosionSnapshot explosion(7, Position(50, 60), TextureFigure::CowboyBullet);

    std::vector<uint16_t> buffer;

    protocol.create_buffer_explosion(explosion, buffer);

    EXPECT_EQ(buffer.size(), 4);

    EXPECT_EQ(buffer[0], static_cast<uint16_t>(htons(static_cast<uint16_t>(explosion.id))));
    EXPECT_EQ(buffer[1], static_cast<uint16_t>(htons(static_cast<uint16_t>(explosion.texture))));
    EXPECT_EQ(buffer[2], static_cast<uint16_t>(htons(static_cast<uint16_t>(explosion.position.x))));
    EXPECT_EQ(buffer[3], static_cast<uint16_t>(htons(static_cast<uint16_t>(explosion.position.y))));
}

TEST(ServerProtocolTest, TestMapComponentBuffer) {
    MockSocket mock_socket("9999");
    ServerProtocol protocol(mock_socket);

    uint16_t pos_x = 5;
    uint16_t pos_y = 2;
    Component type = Component::BIG_WALL;

    MapComponent component(pos_x, pos_y, type);

    std::vector<uint16_t> buffer;

    protocol.create_buffer_map_component(component, buffer);

    EXPECT_EQ(buffer.size(), 3); // Debería tener 3 elementos
    EXPECT_EQ(buffer[0], htons(static_cast<uint16_t>(component.type)));
    EXPECT_EQ(buffer[1], htons(static_cast<uint16_t>(component.x)));
    EXPECT_EQ(buffer[2], htons(static_cast<uint16_t>(component.y)));
}


TEST(ServerProtocolTest, TestBoxBuffer) {
    MockSocket mock_socket("9999");
    ServerProtocol protocol(mock_socket);
    BoxSnapshot box(Position(50, 60), Box::BOX_4_HP);

    std::vector<uint16_t> buffer;

    protocol.create_buffer_box(box, buffer);

    EXPECT_EQ(buffer.size(), 3); // Debería tener 3 elementos
    EXPECT_EQ(buffer[0], htons(static_cast<uint16_t>(box.pos.x)));
    EXPECT_EQ(buffer[1], htons(static_cast<uint16_t>(box.pos.y)));
    EXPECT_EQ(buffer[2], htons(static_cast<uint16_t>(box.status)));
}

