#ifndef GAME_H
#define GAME_H

#include "../../common/constant_rate_loop.h"
#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/defs.h"
#include "../../common/snapshots.h"
#include "../../common/client_actions.h"
#include "./command/gamecontext.h"
#include "./command/inputhandler.h"
#include "../model/protocol.h"
#include "../view/SDLWindow.h"
#include <utility>
#include <vector>
#include <cstdint>
#include <atomic>
#include <iostream>

#include <SDL2pp/SDL2pp.hh>

class Game
{
private:
    SDLWindow window;
    std::atomic<bool> keep_running;
    ConstantRateLoop constant_rate_loop;
    Queue<Snapshot> queue_receiver;
    Queue<ClientActionType> queue_sender;
    InputHandler input;
    GameContext game_context;
    Socket socket;
    SDL2pp::Renderer &renderer;
    SDL2pp::Texture &duck_texture;

    SDL2pp::Texture &get_duck_texture();
    SDL2pp::Texture &get_gun_texture(GunType gun);
    void get_and_execute_events();
    void set_xy(DuckSnapshot duck, int frame_ticks, int &src_x, int &src_y);
    void set_renderer(int current_step);
    void update_renderer(int current_step);
    void handle_event(SDL_Event &event);
    void step(unsigned int current_step);

public:
    Game(const char *host, const char *port);
    void run();
    ~Game();
};

#endif // GAME_H