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

class PositionSnapshot
{
public:
    uint16_t pos_x;
    uint16_t pos_y;

    PositionSnapshot(uint16_t x, uint16_t y) : pos_x(x), pos_y(y) {}
    ~PositionSnapshot() {}
};

class GunNoEquippedSnapshot
{
public:
    GunType type;
    uint16_t pos_x;
    uint16_t pos_y;
    GunNoEquippedSnapshot(GunType t, uint16_t x, uint16_t y) : type(t), pos_x(x), pos_y(y) {}
};

class DuckSnapshot
{
public:
    uint16_t id;
    // const uint16_t health;
    PositionSnapshot position;
    DuckAction current_action;
    GunType gun;
    DuckStatus status;

    explicit DuckSnapshot(uint16_t i, PositionSnapshot p_snap, DuckAction action, GunType gun, DuckStatus status) : id(i),
                                                                                                                    position(std::move(p_snap)),
                                                                                                                    current_action(action),
                                                                                                                    gun(gun),
                                                                                                                    status(status) {}
};

class BoxSnapshot
{
public:
    const PositionSnapshot &pos;
    const GunNoEquippedSnapshot &gun;

    BoxSnapshot(PositionSnapshot &p, GunNoEquippedSnapshot &g) : pos(p), gun(g) {}
};

class MapSnapshot
{
public:
    uint16_t style;
    uint16_t size_x;
    uint16_t size_y;
    std::vector<MapComponent> components;
    // std::vector<BoxSnapshot> boxes;

    MapSnapshot() : style(0), size_x(0), size_y(0) {}

    MapSnapshot(const uint16_t &s,
                const uint16_t &s_x,
                const uint16_t &s_y,
                const std::vector<MapComponent> &c)
        : style(s), size_x(s_x), size_y(s_y), components(c) {}

    ~MapSnapshot() {}
};

class Snapshot
{
public:
    std::vector<DuckSnapshot> ducks;
    std::vector<GunNoEquippedSnapshot> guns;
    MapSnapshot map;

    Snapshot() : ducks({}), guns({}) {}
    Snapshot(std::vector<DuckSnapshot> &&d_s,
             std::vector<GunNoEquippedSnapshot> &&g_s,
             MapSnapshot &map_snapshot) : ducks(d_s), guns(g_s), map(map_snapshot) {}
};

#endif // SNAPSHOTS_H
