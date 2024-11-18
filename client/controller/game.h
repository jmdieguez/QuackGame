#ifndef GAME_H
#define GAME_H

#include <utility>
#include <vector>
#include <cstdint>
#include <atomic>
#include <iostream>
#include <SDL2pp/SDL2pp.hh>

#include "../../common/constant_rate_loop.h"
#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/defs.h"
#include "../../common/snapshots.h"
#include "../../common/map.h"
#include "../../common/client_actions.h"
#include "../../common/texturefigure.h"
#include "./command/gamecontext.h"
#include "../model/protocol.h"
#include "../view/SDLInitializer.h"
#include "../common/tiles.h"
#include "../ui/tileset.h"
#include "../model/resource/sound/soundstorage.h"
#include "render/renderstorage.h"
#include "session/sessioncontroller.h"

class Game
{
private:
    SDLInitializer initializer;
    std::atomic<bool> keep_running;
    ConstantRateLoop constant_rate_loop;
    SessionController session;
    Socket socket;
    SDL2pp::Renderer &renderer;
    SDL2pp::Mixer &mixer;
    RenderStorage render_storage;
    SDL2pp::Chunk &get_chunk(SoundType type);

    void get_and_execute_events();
    void set_renderer(int current_step);
    void update_renderer(int current_step);
    void handle_event(SDL_Event &event);
    void play_sound(SoundSnapshot &sound_snapshot);
    void step(unsigned int current_step);

public:
    Game(Socket);
    void run();
    ~Game();
};

#endif // GAME_H