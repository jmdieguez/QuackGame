#include "game.h"

#define DEFAULT_SIZE_X 1024 // 32x32 tiles
#define DEFAULT_SIZE_Y 1024

Game::Game() : map(DEFAULT_SIZE_X, DEFAULT_SIZE_Y) {}

void Game::process([[maybe_unused]] ClientCommand &command) {
    // En base a qué cliente envío el comando, aplicar cambios en su pato
}

void Game::step() {
    for (Duck duck : ducks) {
        duck.step();
    }
}

Snapshot Game::get_status() {
    MapSnapshot map_snapshot = map.get_status();
    
    std::vector<DuckSnapshot> duck_snapshots;
    for (Duck duck : ducks) {
        duck_snapshots.push_back(duck.get_status());
    }

    return Snapshot(std::move(duck_snapshots));
}