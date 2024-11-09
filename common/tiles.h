#ifndef COMMON_TILE_H
#define COMMON_TILE_H

#include <map>
#include <utility>
#include <string>
#include <cstdint>

#include "../common/map.h"

struct Tiles {
public:
    std::map<std::pair<uint16_t, uint16_t>, Component> tiles_map;
    std::map<std::pair<uint16_t, uint16_t>, Spawn> spawns_map;
    std::map<std::pair<uint16_t, uint16_t>, Box> boxes_map;
};

#endif // COMMON_TILE_H