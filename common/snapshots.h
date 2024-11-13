//
//
// Created by trini-taller on 10/21/24.
//

#ifndef SNAPSHOTS_H
#define SNAPSHOTS_H

#include <cstdint>
#include <vector>

#include "map.h"
#include "duck.h"
#include "gun_type.h"
#include "projectiletype.h"
#include "soundtype.h"
#include "position.h"
#include "projectiledirection.h"
#include "size.h"

class GunNoEquippedSnapshot
{
public:
    GunType type;
    Position position;
    Size size;
    uint16_t angle;
    explicit GunNoEquippedSnapshot(const GunType &t, const Position &p, const Size &s, const uint16_t &angle) : type(t), position(p), size(s), angle(angle) {}
};

class ProjectileSnapshot
{
public:
    uint16_t pos_x;
    uint16_t pos_y;
    ProjectileType type;
    ProjectileDirection type_direction;
    bool finish;
    explicit ProjectileSnapshot(uint16_t x, uint16_t y, ProjectileType type, ProjectileDirection type_direction, bool finish) : pos_x(x), pos_y(y), type(type), type_direction(type_direction), finish(finish) {}
};

class DuckSnapshot
{
public:
    uint16_t id;
    Position position;
    Size size_duck;
    GunType gun;
    Size size_gun;
    Position position_gun;
    uint16_t angle_gun;
    DuckStatus status;

    explicit DuckSnapshot(const uint16_t &i, const Position &p, const Size &size_duck, const GunType &gun, const Size &size_gun, const Position &position_gun, const uint16_t &angle_gun, const DuckStatus &status) : id(i),
                                                                                                                                                                                                                      position(std::move(p)),
                                                                                                                                                                                                                      size_duck(size_duck),
                                                                                                                                                                                                                      gun(gun),
                                                                                                                                                                                                                      size_gun(size_gun),
                                                                                                                                                                                                                      position_gun(position_gun),
                                                                                                                                                                                                                      angle_gun(angle_gun),
                                                                                                                                                                                                                      status(status)
    {
    }
};

class SoundSnapshot
{
public:
    SoundType sound;
    explicit SoundSnapshot(const SoundType &sound) : sound(sound) {}
};

class ExplosionSnapshot
{
public:
    uint16_t pos_x;
    uint16_t pos_y;
    uint16_t phase;
    explicit ExplosionSnapshot(uint16_t pos_x, uint16_t pos_y) : pos_x(pos_x), pos_y(pos_y), phase(0) {}
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
    std::vector<BoxSnapshot> boxes;
    std::vector<Position> gun_spawns;

    MapSnapshot() : style(0), size_x(0), size_y(0) {}

    MapSnapshot(const uint16_t &s,
                const uint16_t &s_x,
                const uint16_t &s_y,
                const std::vector<MapComponent> &c,
                const std::vector<BoxSnapshot> &b,
                const std::vector<Position> &g)
        : style(s), size_x(s_x), size_y(s_y), components(c), boxes(b), gun_spawns(g) {}

    ~MapSnapshot() {}
};

class Snapshot
{
public:
    std::vector<DuckSnapshot> ducks;
    std::vector<GunNoEquippedSnapshot> guns;
    std::vector<ProjectileSnapshot> projectiles;
    std::vector<SoundSnapshot> sounds;
    MapSnapshot map;

    Snapshot() : ducks({}), guns({}), projectiles({}), sounds({}) {}
    Snapshot(std::vector<DuckSnapshot> &&d_s,
             std::vector<GunNoEquippedSnapshot> &&g_s,
             std::vector<ProjectileSnapshot> &&p,
             std::vector<SoundSnapshot> &&s,
             MapSnapshot &map_snapshot) : ducks(d_s), guns(g_s), projectiles(p), sounds(s), map(map_snapshot) {}
};

#endif // SNAPSHOTS_H
