#include "game.h"
#include "../model/receiver.h"
#include "../model/sender.h"
#include "../model/resource/texturestorage.h"
#include "../common/texturefigure.h"
#include "../common/texturesize.h"

#define MAX_MESSAGES_QUEUE_RECEIVER 100000
#define MAX_MESSAGES_QUEUE_SENDER 100000

#define POS_INIT_X_GUN 0
#define POS_INIT_Y_GUN 0
#define SRC_GUN_WIDTH 300
#define SRC_GUN_HEIGHT 300

#define POS_INIT_X_PROJECTILE 0
#define POS_INIT_Y_PROJECTILE 0
#define SRC_PROJECTILE_WIDTH 60
#define SRC_PROJECTILE_HEIGHT 60

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/
SDL2pp::Texture &Game::get_texture(TextureFigure figure)
{
    TextureStorage &storage = TextureStorage::get_instance();
    std::shared_ptr<Texture> texture_created = storage.get_texture(renderer, figure);
    return texture_created.get()->get_texture();
}

SDL2pp::Chunk &Game::get_chunk(SoundType type)
{
    SoundStorage &storage = SoundStorage::get_instance();
    std::shared_ptr<Sound> sound_created = storage.get_sound(type);
    return sound_created.get()->get_Sound();
}

void Game::handle_event(SDL_Event &event)
{
    if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_END)
        keep_running = false;
    else if (event.type == SDL_KEYDOWN)
        input.execute_command(event, game_context, cheat_storage);
    else if (event.type == SDL_KEYUP)
        input.undo_command(event, game_context);
}

void Game::get_and_execute_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
        handle_event(event);
}

void Game::update_renderer(int frame_ticks)
{
    renderer.Clear();
    set_renderer(frame_ticks);
    renderer.Present();
}

void Game::render_projectile(ProjectileSnapshot &projectile)
{

    SDL2pp::Texture &texture = get_texture(projectile.texture);
    int src_x = POS_INIT_X_PROJECTILE, src_y = POS_INIT_Y_PROJECTILE;
    bool looking_right = projectile.type_direction == ProjectileDirection::Right;
    SDL_RendererFlip flip = looking_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    SDL_Rect src_rect = {src_x, src_y, SRC_PROJECTILE_WIDTH, SRC_PROJECTILE_HEIGHT};
    uint16_t dst_rect_x = projectile.pos_x + (looking_right ? HORIZONTAL_RIGHT : HORIZONTAL_LEFT);
    SDL_Rect dst_rect = {dst_rect_x, projectile.pos_y + HORIZONTAL_Y, PROJECTILE_WIDTH, PROJECTILE_HEIGHT};
    SDL_RenderCopyEx(renderer.Get(), texture.Get(), &src_rect, &dst_rect, 0.0, nullptr, flip);
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

void Game::render_spawn_in_map(Position &p)
{
    SDL2pp::Texture &texture = get_texture(TextureFigure::Spawn_T);
    int width = texture.GetWidth();
    int height = texture.GetHeight();
    SDL_Rect src_rect = {0, 0, width, height};
    int x = (p.x * TILE_SIZE) + ((TILE_SIZE - width) / 2);
    int y = (p.y * TILE_SIZE) + (TILE_SIZE - height);
    SDL_Rect dst_rect = {x, y, width, height};
    renderer.Copy(texture, src_rect, dst_rect);
}

void Game::play_sound(SoundSnapshot &sound_snapshot)
{
    SDL2pp::Chunk &sound = get_chunk(sound_snapshot.sound);
    sound.SetVolume(1);
    mixer.PlayChannel(-1, sound);
}

void Game::set_renderer(int frame_ticks)
{
    render_storage.get_scene().render();
    Snapshot snapshot;
    if (!queue_receiver.try_pop(snapshot))
        return;
    for (MapComponent &component : snapshot.map.components)
        render_component_in_map(component, snapshot.map.style);
    for (BoxSnapshot &box : snapshot.map.boxes)
        render_storage.get_box_item().render(box);
    for (Position &position : snapshot.map.gun_spawns)
        render_spawn_in_map(position);
    for (DuckSnapshot &duck_snapshot : snapshot.ducks)
        render_storage.get_duck().render(duck_snapshot, frame_ticks);
    for (GunNoEquippedSnapshot &gun : snapshot.guns)
        render_storage.get_item().render(gun);
    for (ProjectileSnapshot &projectile : snapshot.projectiles)
        render_projectile(projectile);
    for (SoundSnapshot &sound_snapshot : snapshot.sounds)
        play_sound(sound_snapshot);
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

Game::Game(Socket skt)
    : keep_running(true),
      constant_rate_loop(keep_running, [this](unsigned int step)
                         { this->step(step); }),
      queue_receiver(MAX_MESSAGES_QUEUE_RECEIVER),
      queue_sender(MAX_MESSAGES_QUEUE_SENDER),
      input(queue_sender),
      game_context(queue_sender),
      socket(std::move(skt)),
      renderer(initializer.get_renderer()),
      mixer(initializer.get_mixer()),
      render_storage(renderer),
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
