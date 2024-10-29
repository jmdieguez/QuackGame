#ifndef SERVER_MAP_H
#define SERVER_MAP_H

#include "../../common/snapshots.h"

class Map {
private:
    uint16_t tileset_style;
    uint16_t size_x;
    uint16_t size_y;
    std::vector<MapComponent> components;

public:
    Map(uint16_t style, uint16_t x, uint16_t y) : tileset_style(style), size_x(x), size_y(y) {}
    ~Map() {}
    
    MapSnapshot get_status() { return MapSnapshot(size_x, size_y, components); }
};

#endif // SERVER_MAP_H
