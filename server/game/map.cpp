#include "map.h"

Map::Map(uint16_t s_x, uint16_t s_y) : size_x(s_x), size_y(s_y) {}

MapSnapshot Map::get_status() {
    return MapSnapshot(size_x, size_y);
}