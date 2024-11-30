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
#include "music/musicboxstorage.h"
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
    RenderStorage render_storage;
    MusicBoxStorage music_storage;
    Socket socket;
    bool started = false;
    bool victory;
    uint16_t round = 0;

    void get_and_execute_events();
    void set_renderer(int current_step);
    void update_renderer(int current_step);
    void handle_event(SDL_Event &event);
    void step(unsigned int current_step);
    void process_explosion(ExplosionSnapshot &explosion, int frame_ticks, Snapshot &snapshot, float scale_x, float scale_y);
    void process_projectile(ProjectileSnapshot &projectile, Snapshot &snapshot, float scale_x, float scale_y);

public:
    Game(Socket);
    bool run();
    ~Game();
};

#endif // GAME_H
