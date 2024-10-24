#ifndef GAME_H
#define GAME_H

#include "../../common/constant_rate_loop.h"
#include "../../common/queue.h"
#include "../../common/defs.h"
#include "../../common/snapshots.h"
#include "./command/gamecontext.h"
#include "./command/inputhandler.h"
// #include "../model/network.h"
#include <utility>
#include <vector>
#include <cstdint>
#include <atomic>
#include <iostream>

#include <SDL2pp/SDL2pp.hh>

class Game
{
private:
    std::atomic<bool> keep_running;
    int run_phase;
    float position;
    unsigned int prev_ticks;
    ConstantRateLoop constant_rate_loop;
    SDL2pp::Renderer &duck_renderer;
    SDL2pp::Texture &duck_sprites;
    Queue<std::vector<Snapshot>> queue_receiver;
    Queue<std::vector<uint8_t>> queue_sender;
    // Network network;
    InputHandler input;
    GameContext game_context;

    void step(unsigned int current_step);

public:
    explicit Game(SDL2pp::Renderer &renderer, SDL2pp::Texture &sprites);
    void run();
    ~Game();
};

#endif // GAME_H