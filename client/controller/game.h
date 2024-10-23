#include "../../common/constant_rate_loop.h"
#include "../../common/queue.h"
#include "../../common/defs.h"
#include "../model/network.h"
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
    bool right_direction;
    bool is_running;
    bool is_bent_down;
    int run_phase;
    float position;
    unsigned int prev_ticks;

    ConstantRateLoop constant_rate_loop;
    SDL2pp::Renderer &duck_renderer;
    SDL2pp::Texture &duck_sprites;
    Queue<std::vector<Snapshot>> queue_receiver;
    Queue<std::vector<uint8_t>> queue_sender;
    Network network;

    void step(unsigned int current_step);

public:
    explicit Game(SDL2pp::Renderer &renderer, SDL2pp::Texture &sprites);
    void run();
    ~Game();
};
