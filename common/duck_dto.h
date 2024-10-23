#ifndef COMMON_DUCK_DTO_H
#define COMMON_DUCK_DTO_H

#include "gun_dto.h"

class DuckDTO {
public:
    const std::pair<uint16_t, uint16_t> position;
    const std::pair<uint8_t, uint8_t> direction;
    const bool has_chestplate;
    const bool has_helmet;
    const bool is_alive;
    const GunDTO gun_dto;

    DuckDTO(const std::pair<uint16_t, uint16_t> &p, const std::pair<uint8_t, uint8_t> &d,
            const bool &has_c, const bool &has_h, const bool &is_al, const GunDTO &g_dto) :
            position(p), direction(d), has_chestplate(has_c), has_helmet(has_h), is_alive(is_al), gun_dto(g_dto) {}
};

#endif // COMMON_DUCK_DTO_H
