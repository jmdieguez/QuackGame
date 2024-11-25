#include "game.h"

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

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
    initializer.get_renderer().Clear();
    set_renderer(frame_ticks);
    initializer.get_renderer().Present();
}

void Game::set_renderer(int frame_ticks)
{
    render_storage.get_scene().render();
    Snapshot snapshot;

    // aca quieren poppear mas de un snapshot por loop (y quedarse con el ultimo)
    // esto es lo que les genera input lag
    while (session.get_queue_receiver().try_pop(snapshot));
    if (!started) {
        loading_screen.render();
        started = true;
        return;
    }

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
    // for (SoundSnapshot &sound_snapshot : snapshot.sounds)
    //     music_box.play_sound(sound_snapshot);
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
      font(FONT_PATH, 32),
      loading_screen(initializer.get_renderer(), font),
      music_box(initializer.get_mixer()),
      render_storage(initializer.get_renderer()),
      socket(std::move(skt))
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
