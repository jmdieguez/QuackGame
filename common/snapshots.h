
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
#include "texturefigure.h"
#include "color.h"

class GunNoEquippedSnapshot
{
public:
    TextureFigure texture;
    Position position;
    Size size;
    uint16_t angle;
    explicit GunNoEquippedSnapshot(const TextureFigure &t, const Position &p, const Size &s, const uint16_t &angle) : texture(t), position(p),
                                                                                                                      size(s), angle(angle) {}
};

class ProjectileSnapshot
{
public:
    uint16_t pos_x;
    uint16_t pos_y;
    Size size;
    ProjectileType type;
    TextureFigure texture;
    ProjectileDirection type_direction;
    bool finish;
    explicit ProjectileSnapshot(const uint16_t &x, const uint16_t &y, const Size &s, const ProjectileType &type, const TextureFigure &texture, const ProjectileDirection &type_direction, bool finish) : pos_x(x), pos_y(y),
                                                                                                                                                                                                         size(s), type(type),
                                                                                                                                                                                                         texture(texture), type_direction(type_direction),
                                                                                                                                                                                                         finish(finish) {}
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

class SoundSnapshot
{
public:
    SoundType sound;
    explicit SoundSnapshot(const SoundType &sound) : sound(sound) {}
};

class ExplosionSnapshot
{
public:
    Size size;
    Position position;
    TextureFigure texture;
    explicit ExplosionSnapshot(const Size &size, const Position &position, const TextureFigure &texture) : size(size), position(position),
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

class Snapshot
{
public:
    std::vector<DuckSnapshot> ducks;
    std::vector<GunNoEquippedSnapshot> guns;
    std::vector<ProjectileSnapshot> projectiles;
    std::vector<ExplosionSnapshot> explosions;
    std::vector<SoundSnapshot> sounds;
    std::vector<BoxSnapshot> boxes;
    MapSnapshot map;

    Snapshot() : ducks({}), guns({}), projectiles({}), explosions({}), sounds({}) {}
    
    Snapshot(std::vector<DuckSnapshot> &&d_s,
             std::vector<GunNoEquippedSnapshot> &&g_s,
             std::vector<ProjectileSnapshot> &&p,
             std::vector<ExplosionSnapshot> &&e,
             std::vector<SoundSnapshot> &&s,
             std::vector<BoxSnapshot> &&b,
             
             MapSnapshot &map_snapshot)
              : ducks(d_s), guns(g_s), projectiles(p), explosions(e),
                sounds(s), boxes(b), map(map_snapshot) {}
};

#endif // SNAPSHOTS_H
