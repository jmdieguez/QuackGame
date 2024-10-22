#include "game.h"

#define MAX_MESSAGES_QUEUE_RECEIVER 100000
#define MAX_MESSAGES_QUEUE_SENDER 100000

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Game::Game() : keep_running(true), constant_rate_loop(keep_running, FRAME_RATE, [this](unsigned int step)
                                                      { this->step(step); }),
               queue_receiver(MAX_MESSAGES_QUEUE_RECEIVER), queue_sender(MAX_MESSAGES_QUEUE_SENDER), network(keep_running, queue_receiver, queue_sender) {}

void Game::run()
{
    network.run();
    constant_rate_loop.execute();
    network.join();
}

void Game::step(unsigned int current_step)
{
}

Game::~Game() {}
