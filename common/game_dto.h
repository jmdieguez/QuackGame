#ifndef COMMON_GAME_DTO
#define COMMON_GAME_DTO

#include "map_dto.h"

class GameDTO {
public:
    // acá se guardarian todo lo relacionado al estado actual del juego:
    // mapa, patos, drops, balas, etc
    const MapDTO map_dto;
    GameDTO(MapDTO &m_dto) : map_dto(m_dto) {}
    ~GameDTO() {}
};

#endif // COMMON_GAME_DTO
