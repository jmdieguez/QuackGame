#ifndef GAME_H
#define GAME_H

#include <utility>
#include <vector>
#include <cstdint>
#include <atomic>
#include <iostream>

#include "../view/SDLInitializer.h"
#include "../model/receiver.h"
#include "../model/sender.h"
#include "../../common/constant_rate_loop.h"
#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/snapshots.h"
#include "render/renderstorage.h"
#include "session/sessioncontroller.h"
#include "music/musicbox.h"
#include "../view/loading_screen.h"

class Game
{
private:
    SDLInitializer initializer;
    std::atomic<bool> keep_running;
    ConstantRateLoop constant_rate_loop;
    SDL2pp::Font font;
    LoadingScreen loading_screen;
    SessionController session;
    MusicBox music_box;
    RenderStorage render_storage;
    Socket socket;
    bool started = false;

    void get_and_execute_events();
    void set_renderer(int current_step);
    void update_renderer(int current_step);
    void handle_event(SDL_Event &event);
    void step(unsigned int current_step);

public:
    Game(Socket);
    void run();
    ~Game();
};

#endif // GAME_H
