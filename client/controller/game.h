#ifndef GAME_H
#define GAME_H

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
#include "../view/SDLWindow.h"
#include "../common/tiles.h"
#include "../ui/tileset.h"
#include <utility>
#include <vector>
#include <cstdint>
#include <atomic>
#include <iostream>

#include <SDL2pp/SDL2pp.hh>

#define TILESETS "/var/quackgame/tiles.png"

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
    SDL2pp::Texture &background_texture;
    SDL2pp::Texture &duck_texture;
    SDL2pp::Texture &get_background_texture();
    SDL2pp::Texture &get_duck_texture();
    SDL2pp::Texture &get_spawn_texture();
    SDL2pp::Texture &get_gun_texture(GunType gun);
    SDL2pp::Texture &get_box_texture();
    SDL2pp::Texture &get_projectile_texture(ProjectileType projectile);
    SDL2pp::Texture &get_texture(TextureFigure figure);

    std::shared_ptr<SDL2pp::Texture> all_tilesets_texture;
    std::map<uint8_t, std::unique_ptr<Tileset>> tilesets;
    std::map<Component, std::pair<uint8_t, uint8_t>> dimensions;

    void get_and_execute_events();
    void set_xy(DuckSnapshot &duck, int frame_ticks, int &src_x, int &src_y);
    void set_renderer(int current_step);
    void render_background();
    void render_duck_with_gun(DuckSnapshot &duck, int frame_ticks);
    void render_duck(DuckSnapshot &duck, int frame_ticks);
    void render_helmet_chestplate(DuckSnapshot &duck);
    void render_weapon(DuckSnapshot &duck);
    void render_weapon_in_map(GunNoEquippedSnapshot &gun);
    void render_component_in_map(MapComponent &component, uint16_t &style);
    void render_projectile(ProjectileSnapshot &projectile);
    void render_box_in_map(BoxSnapshot &box);
    void render_spawn_in_map(Position &p);
    void update_renderer(int current_step);
    void handle_event(SDL_Event &event);
    void step(unsigned int current_step);

public:
    Game(const char *host, const char *port);
    void run();
    ~Game();
};

#endif // GAME_H