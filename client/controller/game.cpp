#include "game.h"
#include "../model/receiver.h"
#include "../model/sender.h"
#include "../model/resource/texturestorage.h"
#include "../common/texturefigure.h"
#include "../common/texturesize.h"

#define MAX_MESSAGES_QUEUE_RECEIVER 100000
#define MAX_MESSAGES_QUEUE_SENDER 100000

#define DEFAULT_WINDOW_WIDTH 480
#define DEFAULT_WINDOW_HEIGHT 640

#define SRC_DUCK_WIDTH 32
#define SRC_DUCK_HEIGHT 32
#define POS_INIT_X_IMAGE 1
#define POS_INIT_Y_IMAGE 8

#define POS_INIT_X_GUN 0
#define POS_INIT_Y_GUN 0
#define SRC_GUN_WIDTH 300
#define SRC_GUN_HEIGHT 300

#define POS_INIT_X_PROJECTILE 0
#define POS_INIT_Y_PROJECTILE 0
#define SRC_PROJECTILE_WIDTH 60
#define SRC_PROJECTILE_HEIGHT 60

#define CHESTPLATE_WIDTH 20
#define CHESTPLATE_HEIGHT 15

#define HELMET_WIDTH 20
#define HELMET_HEIGHT 20

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

SDL2pp::Texture &Game::get_duck_texture()
{
    TextureStorage &storage = TextureStorage::get_instance();
    std::shared_ptr<Texture> texture_created = storage.get_texture(renderer, TextureFigure::DUCK);
    return texture_created.get()->get_texture();
}

SDL2pp::Texture &Game::get_gun_texture(GunType gun)
{
    TextureStorage &storage = TextureStorage::get_instance();
    std::shared_ptr<Texture> texture_created = storage.get_texture(renderer, gun);
    return texture_created.get()->get_texture();
}

SDL2pp::Texture &Game::get_box_texture()
{
    TextureStorage &storage = TextureStorage::get_instance();
    std::shared_ptr<Texture> texture_created = storage.get_texture(renderer, TextureFigure::Box_T);
    return texture_created.get()->get_texture();
}

SDL2pp::Texture &Game::get_projectile_texture(ProjectileType projectile)
{
    TextureStorage &storage = TextureStorage::get_instance();
    std::shared_ptr<Texture> texture_created = storage.get_texture(renderer, projectile);
    return texture_created.get()->get_texture();
}

SDL2pp::Texture &Game::get_texture(TextureFigure figure)
{
    TextureStorage &storage = TextureStorage::get_instance();
    std::shared_ptr<Texture> texture_created = storage.get_texture(renderer, figure);
    return texture_created.get()->get_texture();
}

void Game::handle_event(SDL_Event &event)
{
    if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_END)
        keep_running = false;
    else if (event.type == SDL_KEYDOWN)
        input.execute_command(event, game_context);
    else if (event.type == SDL_KEYUP)
        input.undo_command(event, game_context);
}

void Game::get_and_execute_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
        handle_event(event);
}

void Game::set_xy(DuckSnapshot &duck, int frame_ticks, int &src_x, int &src_y)
{

    if (!duck.status.is_alive)
        src_y += DUCK_HEIGHT * 2;

    else if (duck.status.bent_down)
        src_y += DUCK_HEIGHT * 2;
    else if (duck.current_action == DuckAction::MOVING)
    {
        int run_phase = (frame_ticks / 4) % 5 + 1;
        src_x = SRC_DUCK_WIDTH * run_phase;
    }
}

void Game::update_renderer(int frame_ticks)
{
    renderer.Clear();
    set_renderer(frame_ticks);
    renderer.Present();
}

void Game::render_duck(DuckSnapshot &duck, int frame_ticks)
{
    int src_x = POS_INIT_X_IMAGE, src_y = POS_INIT_Y_IMAGE;
    set_xy(duck, frame_ticks, src_x, src_y);
    SDL_Rect src_rect = {src_x, src_y, SRC_DUCK_WIDTH, SRC_DUCK_HEIGHT};
    SDL_Rect dst_rect = {duck.position.x, duck.position.y, duck.size_duck.width, duck.size_duck.height};
    SDL_RendererFlip flip = duck.status.looking_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(renderer.Get(), duck_texture.Get(), &src_rect, &dst_rect, 0.0, nullptr, flip);
}

void Game::render_helmet_chestplate(DuckSnapshot &duck)
{
    int src_x = POS_INIT_X_IMAGE, src_y = POS_INIT_Y_IMAGE;
    if (duck.status.has_chestplate)
    {
        SDL2pp::Texture &chestplate_texture = get_texture(TextureFigure::Chestplate);
        SDL_Rect src_rect = {src_x, src_y, SRC_DUCK_WIDTH, SRC_DUCK_HEIGHT};
        SDL_Rect dst_rect = {duck.position.x + (duck.status.looking_right ? 3 : 8), duck.position.y + 15, CHESTPLATE_WIDTH, CHESTPLATE_HEIGHT};
        SDL_RendererFlip flip = duck.status.looking_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(renderer.Get(), chestplate_texture.Get(), &src_rect, &dst_rect, 0.0, nullptr, flip);
    }
    if (duck.status.has_helmet)
    {
        SDL2pp::Texture &helmet = get_texture(TextureFigure::Helmet);
        SDL_Rect src_rect = {src_x, src_y, SRC_DUCK_WIDTH, SRC_DUCK_HEIGHT};
        SDL_Rect dst_rect = {duck.position.x + (duck.status.looking_right ? 3 : 8), duck.position.y - 2, HELMET_WIDTH, HELMET_HEIGHT};
        SDL_RendererFlip flip = duck.status.looking_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(renderer.Get(), helmet.Get(), &src_rect, &dst_rect, 0.0, nullptr, flip);
    }
}
void Game::render_weapon(DuckSnapshot &duck)
{
    SDL2pp::Texture &texture = get_gun_texture(duck.gun);
    int src_x = POS_INIT_X_GUN, src_y = POS_INIT_Y_GUN;
    SDL_RendererFlip flip = duck.status.looking_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    SDL_Rect src_rect = {src_x, src_y, SRC_GUN_WIDTH, SRC_GUN_HEIGHT};
    SDL_Rect dst_rect = {duck.position_gun.x, duck.position_gun.y, duck.size_gun.width, duck.size_gun.height};
    SDL_RenderCopyEx(renderer.Get(), texture.Get(), &src_rect, &dst_rect, duck.angle_gun, nullptr, flip);
}

void Game::render_projectile(ProjectileSnapshot &projectile)
{

    SDL2pp::Texture &texture = get_projectile_texture(projectile.type);
    int src_x = POS_INIT_X_PROJECTILE, src_y = POS_INIT_Y_PROJECTILE;
    bool looking_right = projectile.type_direction == ProjectileDirection::Right;
    SDL_RendererFlip flip = looking_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    SDL_Rect src_rect = {src_x, src_y, SRC_PROJECTILE_WIDTH, SRC_PROJECTILE_HEIGHT};
    uint16_t dst_rect_x = projectile.pos_x + (looking_right ? HORIZONTAL_RIGHT : HORIZONTAL_LEFT);
    SDL_Rect dst_rect = {dst_rect_x, projectile.pos_y + HORIZONTAL_Y, PROJECTILE_WIDTH, PROJECTILE_HEIGHT};
    SDL_RenderCopyEx(renderer.Get(), texture.Get(), &src_rect, &dst_rect, 0.0, nullptr, flip);
}

void Game::render_weapon_in_map(GunNoEquippedSnapshot &gun)
{
    SDL2pp::Texture &texture = get_gun_texture(gun.type);
    int src_x = POS_INIT_X_GUN, src_y = POS_INIT_Y_GUN;
    SDL_Rect src_rect = {src_x, src_y, SRC_GUN_WIDTH, SRC_GUN_HEIGHT};
    SDL_Rect dst_rect = {gun.position.x, gun.position.y + GUN_HEIGHT, gun.size.width, gun.size.height};
    SDL_RenderCopyEx(renderer.Get(), texture.Get(), &src_rect, &dst_rect, 0.0, nullptr, SDL_FLIP_NONE);
}

void Game::render_duck_with_gun(DuckSnapshot &duck, int frame_ticks)
{
    render_duck(duck, frame_ticks);
    render_helmet_chestplate(duck);
    if (duck.gun != GunType::None)
        render_weapon(duck);
}

void Game::render_component_in_map(MapComponent &component, uint16_t &style)
{
    std::unique_ptr<Tileset> &tileset = tilesets[style];
    std::shared_ptr<SDL2pp::Texture> &texture = tileset->textures[component.type];
    uint8_t dim_x = dimensions[component.type].first;
    uint8_t dim_y = dimensions[component.type].second;
    SDL_Rect src_rect = {0, 0, dim_x, dim_y};
    SDL_Rect dst_rect = {component.x * TILE_SIZE, component.y * TILE_SIZE, dim_x, dim_y};
    renderer.Copy(*texture, src_rect, dst_rect);
}

void Game::render_box_in_map(BoxSnapshot &box)
{
    if (box.status != Box::NONE)
    {
        SDL2pp::Texture &texture = get_box_texture();
        int x = static_cast<int>(box.status) * texture.GetHeight();
        SDL_Rect src_rect = {x, 0, texture.GetHeight(), texture.GetHeight()};
        SDL_Rect dst_rect = {box.pos.x * TILE_SIZE, box.pos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
        renderer.Copy(texture, src_rect, dst_rect);
    }
}

void Game::set_renderer(int frame_ticks)
{
    Snapshot snapshot;
    if (!queue_receiver.try_pop(snapshot))
        return;
    for (DuckSnapshot &duck : snapshot.ducks)
        render_duck_with_gun(duck, frame_ticks);
    for (GunNoEquippedSnapshot &gun : snapshot.guns)
        render_weapon_in_map(gun);
    for (ProjectileSnapshot &projectile : snapshot.projectiles)
        render_projectile(projectile);
    for (MapComponent &component : snapshot.map.components)
        render_component_in_map(component, snapshot.map.style);
    for (BoxSnapshot &box : snapshot.map.boxes)
    {
        render_box_in_map(box);
    }
}

void Game::step(unsigned int current_step)
{
    unsigned int frame_ticks = current_step;
    get_and_execute_events();
    update_renderer(frame_ticks);
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Game::Game(const char *host, const char *port)
    : keep_running(true),
      constant_rate_loop(keep_running, [this](unsigned int step)
                         { this->step(step); }),
      queue_receiver(MAX_MESSAGES_QUEUE_RECEIVER),
      queue_sender(MAX_MESSAGES_QUEUE_SENDER),
      input(queue_sender),
      game_context(queue_sender),
      socket(host, port),
      renderer(window.get_renderer()),
      duck_texture(get_duck_texture()),
      all_tilesets_texture(std::make_shared<SDL2pp::Texture>(renderer, TILESETS))
{
    YAML::Node root = YAML::LoadFile(DIMENSIONS_FILE);
    for (const auto &dim : root["components"])
    {
        Component type = dim["type"].as<Component>();
        uint16_t dim_x = dim["dim_x"].as<uint16_t>(); // n tiles
        uint16_t dim_y = dim["dim_y"].as<uint16_t>();
        dimensions.emplace(type, std::make_pair(dim_x * TILE_SIZE, dim_y * TILE_SIZE));
    }

    int n_tilesets = 5;

    for (uint8_t i = 0; i < n_tilesets; i++)
        tilesets.emplace(i, std::make_unique<Tileset>(i, renderer, all_tilesets_texture));
}

void Game::run()
{
    Receiver receiver(socket, queue_receiver);
    Sender sender(socket, queue_sender);
    receiver.start();
    sender.start();
    constant_rate_loop.execute();
    receiver.stop();
    sender.stop();
    receiver.join();
    sender.join();
}

Game::~Game() {}
