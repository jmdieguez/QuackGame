#include "../../common/constant_rate_loop.h"
#include "../../common/queue.h"
#include "../../common/defs.h"
#include "../model/network.h"
#include <utility>
#include <vector>
#include <cstdint>
#include <atomic>

class Game
{
private:
    std::atomic<bool> keep_running;
    ConstantRateLoop constant_rate_loop;
    Queue<std::vector<uint8_t>> queue_receiver;
    Queue<std::vector<uint8_t>> queue_sender;
    Network network;

public:
    Game();
    void run();
    void step(unsigned int current_step);
    ~Game();
};
