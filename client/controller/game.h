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
#include "./command/inputhandler.h"
#include "../model/protocol.h"
#include "../view/SDLInitializer.h"
#include "../common/tiles.h"
#include "../ui/tileset.h"
#include "cheats/cheatstorage.h"
#include "../model/resource/sound/soundstorage.h"
#include "render/renderstorage.h"

#define TILESETS "/var/quackgame/tiles.png"

class Game
{
private:
    SDLInitializer initializer;
    std::atomic<bool> keep_running;
    CheatStorage cheat_storage;
    ConstantRateLoop constant_rate_loop;
    Queue<Snapshot> queue_receiver;
    Queue<ClientActionType> queue_sender;
    InputHandler input;
    GameContext game_context;
    Socket socket;
    SDL2pp::Renderer &renderer;
    SDL2pp::Mixer &mixer;
    RenderStorage render_storage;
    SDL2pp::Texture &get_texture(TextureFigure figure);
    SDL2pp::Chunk &get_chunk(SoundType type);

    std::shared_ptr<SDL2pp::Texture> all_tilesets_texture;
    std::map<uint8_t, std::unique_ptr<Tileset>> tilesets;
    std::map<Component, std::pair<uint8_t, uint8_t>> dimensions;

    void get_and_execute_events();
    void set_renderer(int current_step);
    void render_component_in_map(MapComponent &component, uint16_t &style);
    void render_projectile(ProjectileSnapshot &projectile);
    void render_box_in_map(BoxSnapshot &box);
    void render_spawn_in_map(Position &p);
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