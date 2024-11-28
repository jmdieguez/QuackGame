
#ifndef SNAPSHOTS_H
#define SNAPSHOTS_H

#include <cstdint>
#include <vector>

#include "armor.h"
#include "map.h"
#include "duck.h"
#include "gun_type.h"
#include "projectiletype.h"
#include "position.h"
#include "projectiledirection.h"
#include "size.h"
#include "texturefigure.h"
#include "color.h"

class ArmorSnapshot
{
public:
    Position position;
    ArmorType type;
    ArmorSnapshot(const Position &p, const ArmorType &t) : position(p), type(t) {}
    ArmorSnapshot() : position(0, 0) {}
};

class GunNoEquippedSnapshot
{
public:
    TextureFigure texture;
    Position position;
    uint16_t angle;
    explicit GunNoEquippedSnapshot(const TextureFigure &t, const Position &p, const uint16_t &angle) : texture(t), position(p),
                                                                                                       angle(angle) {}
};

class ProjectileSnapshot
{
public:
    uint16_t id;
    uint16_t pos_x;
    uint16_t pos_y;
    ProjectileType type;
    TextureFigure texture;
    ProjectileDirection type_direction;
    explicit ProjectileSnapshot(const uint16_t id, const uint16_t &x, const uint16_t &y, const ProjectileType &type, const TextureFigure &texture, const ProjectileDirection &type_direction) : id(id), pos_x(x), pos_y(y),
                                                                                                                                                                                                type(type),
                                                                                                                                                                                                texture(texture), type_direction(type_direction)
    {
    }
};

class DuckSnapshot
{
public:
    uint16_t id;
    Position position;
    GunType type_gun;
    TextureFigure texture_gun;
    Position position_gun;
    uint16_t angle_gun;
    DuckStatus status;
    Color color;

    explicit DuckSnapshot(const uint16_t &i, const Position &p, const GunType &type_gun, const TextureFigure &texture_gun, const Position &position_gun, const uint16_t &angle_gun, const DuckStatus &status, const Color &color) : id(i),
                                                                                                                                                                                                                                    position(std::move(p)),

                                                                                                                                                                                                                                    type_gun(type_gun),
                                                                                                                                                                                                                                    texture_gun(texture_gun),

                                                                                                                                                                                                                                    position_gun(position_gun),
                                                                                                                                                                                                                                    angle_gun(angle_gun),
                                                                                                                                                                                                                                    status(status),
                                                                                                                                                                                                                                    color(color)
    {
    }
};

class ExplosionSnapshot
{
public:
    uint16_t id;
    Position position;
    TextureFigure texture;
    explicit ExplosionSnapshot(const uint16_t &id, const Position &position, const TextureFigure &texture) : id(id), position(position),
                                                                                                             texture(texture) {}
};

class GrenadeSnapshot
{
public:
    uint16_t pos_x;
    uint16_t pos_y;
    uint16_t phase;
    explicit GrenadeSnapshot(uint16_t x, uint16_t y, uint16_t phase) : pos_x(x), pos_y(y), phase(phase) {}
};

class BoxSnapshot
{
public:
    Position pos;
    Box status;
    BoxSnapshot(const Position &p, const Box &s) : pos(p), status(s) {}
};

class MapSnapshot
{
public:
    uint16_t style;
    uint16_t size_x;
    uint16_t size_y;
    std::vector<MapComponent> components;
    std::vector<Position> gun_spawns;

    MapSnapshot() : style(0), size_x(0), size_y(0) {}

    MapSnapshot(const uint16_t &s,
                const uint16_t &s_x,
                const uint16_t &s_y,
                const std::vector<MapComponent> &c,
                const std::vector<Position> &g)
        : style(s), size_x(s_x), size_y(s_y), components(c), gun_spawns(g) {}

    ~MapSnapshot() {}
};

class CameraSnapshot
{
public:
    uint16_t x, y, width, height;

    CameraSnapshot() : x(0), y(0), width(0), height(0) {}

    CameraSnapshot(const uint16_t &x,
                   const uint16_t &y,
                   const uint16_t &w,
                   const uint16_t &h) : x(x), y(y), width(w), height(h) {}

    ~CameraSnapshot() {}
};

class Snapshot
{
public:
    std::vector<DuckSnapshot> ducks;
    std::vector<GunNoEquippedSnapshot> guns;
    std::vector<ProjectileSnapshot> projectiles;
    std::vector<ExplosionSnapshot> explosions;
    std::vector<BoxSnapshot> boxes;
    std::vector<ArmorSnapshot> armors;
    MapSnapshot map;
    CameraSnapshot camera;

    Snapshot() : ducks({}), guns({}), projectiles({}), explosions({}) {}

    Snapshot(std::vector<DuckSnapshot> &&d_s,
             std::vector<GunNoEquippedSnapshot> &&g_s,
             std::vector<ProjectileSnapshot> &p,
             std::vector<ExplosionSnapshot> &e,
             std::vector<BoxSnapshot> &&b,
             std::vector<ArmorSnapshot> &&a,
             MapSnapshot &map_snapshot,
             CameraSnapshot &c)
        : ducks(d_s), guns(g_s), projectiles(p), explosions(e),
          boxes(b), armors(a), map(map_snapshot), camera(c)
    {
    }
};

#endif // SNAPSHOTS_H
