#include "game.h"
#include "../model/receiver.h"
#include "../model/sender.h"
#include "../model/resource/texturestorage.h"
#include "../common/texturefigure.h"
#include "../common/texturesize.h"

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/
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
        session.process_input(event);
    else if (event.type == SDL_KEYUP)
        session.revert_command(event);
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
    if (!session.get_queue_receiver().try_pop(snapshot))
        return;
    for (MapComponent &component : snapshot.map.components)
        render_storage.get_map_drawer().render_component(component, snapshot.map.style);
    for (BoxSnapshot &box : snapshot.map.boxes)
        render_storage.get_box_item().render(box);
    for (Position &position : snapshot.map.gun_spawns)
        render_storage.get_map_drawer().render_spawn_in_map(position);
    for (DuckSnapshot &duck_snapshot : snapshot.ducks)
        render_storage.get_duck().render(duck_snapshot, frame_ticks);
    for (GunNoEquippedSnapshot &gun : snapshot.guns)
        render_storage.get_item().render(gun);
    for (ProjectileSnapshot &projectile : snapshot.projectiles)
        render_storage.get_projectile_drawer().render(projectile);
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
      socket(std::move(skt)),
      renderer(initializer.get_renderer()),
      mixer(initializer.get_mixer()),
      render_storage(renderer)
{
}

void Game::run()
{
    Receiver receiver(socket, session.get_queue_receiver());
    Sender sender(socket, session.get_queue_sender());
    receiver.start();
    sender.start();
    constant_rate_loop.execute();
    receiver.stop();
    sender.stop();
    receiver.join();
    sender.join();
}

Game::~Game() {}
