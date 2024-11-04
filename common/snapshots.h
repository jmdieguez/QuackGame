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
    bool right_direction; // Eliminar cuando se pueda enviar status al cliente

    // const DuckStatus& status;

    explicit DuckSnapshot(uint16_t i, PositionSnapshot p_snap, DuckAction action, GunType gun, bool right_direction) : id(i),
                                                                                                                       position(std::move(p_snap)),
                                                                                                                       current_action(action),
                                                                                                                       gun(gun),
                                                                                                                       right_direction(right_direction) {}
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
    const uint16_t &style;
    const uint16_t &size_x;
    const uint16_t &size_y;
    const std::vector<MapComponent> &components;
    // std::vector<BoxSnapshot> boxes;

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
    Snapshot() : ducks({}), guns({}) {}
    Snapshot(std::vector<DuckSnapshot> &&d_s, std::vector<GunNoEquippedSnapshot> &&g_s) : ducks(d_s), guns(g_s) {}
};

#endif // SNAPSHOTS_H
