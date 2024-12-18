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
#include "sound/soundboxstorage.h"
#include "session/sessioncontroller.h"
#include "music/musicbox.h"
#include "../view/loading_screen.h"
#include "../view/table_screen.h"
#include "round/roundcontroller.h"

class Game
{
private:
    SDLInitializer initializer;
    std::atomic<bool> keep_running;
    ConstantRateLoop constant_rate_loop;
    SDL2pp::Font font;
    LoadingScreen loading_screen;
    SessionController session;
    std::vector<UserLobbyInfo> users;
    uint16_t lastest_round_show_table;
    bool is_showing_table;
    bool finish_showing_table;
    RenderStorage render_storage;
    RoundController round_controller;
    SoundBoxStorage sound_storage;
    MusicBox music;
    bool mute_effect;
    unsigned volume_music;
    bool mute_music;
    Socket socket;
    bool started = false;
    std::string winner;
    uint16_t round = 0;

    void get_and_execute_events();
    void set_renderer(int current_step);
    void update_renderer(int current_step);
    void handle_event(SDL_Event &event);
    void step(unsigned int current_step);
    void process_explosion(ExplosionSnapshot &explosion, int frame_ticks, Snapshot &snapshot, float scale_x, float scale_y);
    void process_projectile(ProjectileSnapshot &projectile, Snapshot &snapshot, float scale_x, float scale_y);

public:
    Game(Socket, std::vector<UserLobbyInfo> users);
    void run(std::string&);
    ~Game();
};

#endif // GAME_H
