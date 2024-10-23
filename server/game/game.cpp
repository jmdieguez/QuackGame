#include "game.h"

#define DEFAULT_SIZE_X 1024 // 32x32 tiles
#define DEFAULT_SIZE_Y 1024

Game::Game() : map(DEFAULT_SIZE_X, DEFAULT_SIZE_Y) {

}

void Game::step() {
    
}

GameDTO Game::get_status() {
    MapDTO map_dto = map.get_status();
    
    std::vector<DuckDTO> duck_dtos;
    for (Duck duck : ducks) {
        duck_dtos.push_back(duck.get_status());
    }

    return GameDTO(map_dto, duck_dtos);
}