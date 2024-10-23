#ifndef SERVER_MAP_H
#define SERVER_MAP_H

#include "../../common/map_dto.h"

class Map {
private:
    uint16_t size_x;
    uint16_t size_y;
public:
    Map(uint16_t s_x, uint16_t s_y);
    ~Map() {}
    MapDTO get_status();
};

#endif // SERVER_MAP_H
