#ifndef COMMON_MAP_DTO_H
#define COMMON_MAP_DTO_H

#include <cstdint>

class MapDTO {
public:
    const uint16_t size_x;
    const uint16_t size_y;
    
    MapDTO(const uint16_t &s_x, const uint16_t &s_y) : size_x(s_x), size_y(s_y) {}
    ~MapDTO() {}
};

#endif // COMMON_MAP_DTO_H
