#include "server_game.h"

Game::Game() {
    boxes[BoxID::BazookaBox] = std::make_unique<Bazooka>();
    boxes[BoxID::ChainsawBox] = std::make_unique<Chainsaw>();
    boxes[BoxID::DeathRayBox] = std::make_unique<DeathRay>();
    boxes[BoxID::ShotgunBox] = std::make_unique<Shotgun>();
}

Game::~Game() {}

int Game::step() {
    int n = 0;  // number of boxes that respawned during the step
    for (const auto& pair: boxes) {
        auto& item = pair.second;
        bool respawned = item->decrease_timer();
        if (respawned)
            n++;
    }
    return n;
}

Reward Game::pickup(const BoxID& box_id) {
    auto it = boxes.find(box_id);
    if (it != boxes.end()) {
        const std::unique_ptr<Item>& item = it->second;
        return item->pickup();
    }
    return Reward();  // undefined reward
}
