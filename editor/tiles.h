#ifndef EDITOR_TILE_H
#define EDITOR_TILE_H

#include <map>
#include <utility>
#include <string>
#include <cstdint>

#include "../common/map.h"

class Tiles {
public:
    std::map<std::pair<uint16_t, uint16_t>, Component> tiles_map;

    void add_tile(uint16_t x, uint16_t y, const Component& component) {
        std::pair<uint16_t, uint16_t> key = std::make_pair(x, y);
        tiles_map[key] = component;
    }

    Tiles() {}
    ~Tiles() {}
};

#endif // EDITOR_TILE_H