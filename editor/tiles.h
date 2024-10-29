#ifndef EDITOR_TILE_H
#define EDITOR_TILE_H

#include <map>
#include <utility>
#include <string>
#include <cstdint>

class Tiles {
public:
    std::map<std::pair<uint16_t, uint16_t>, std::string> tiles_map;

    void add_tile(uint16_t x, uint16_t y, const std::string& state) {
        std::pair<uint16_t, uint16_t> key = std::make_pair(x, y);
        tiles_map[key] = state;
    }

    Tiles() {}
    ~Tiles() {}
};

#endif // EDITOR_TILE_H