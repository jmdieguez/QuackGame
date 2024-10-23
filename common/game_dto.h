#ifndef COMMON_GAME_DTO
#define COMMON_GAME_DTO

#include "duck_dto.h"
#include "map_dto.h"

class GameDTO {
public:
    // acá se guardarian todo lo relacionado al estado actual del juego:
    // mapa, patos, drops, balas, etc
    const MapDTO map_dto;
    const std::vector<DuckDTO> duck_dtos;
    GameDTO(MapDTO &m_dto, std::vector<DuckDTO> &vec) : map_dto(m_dto), duck_dtos(vec) {}
    ~GameDTO() {}
};

#endif // COMMON_GAME_DTO
