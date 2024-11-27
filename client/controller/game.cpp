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
    Snapshot snapshot, latest_snapshot;
    auto &queue = session.get_queue_receiver();
    while (queue.try_pop(snapshot)) { 
        started = true;
        latest_snapshot = snapshot;
    }
    
    if (!started) 
        loading_screen.render();
    else {
        if (latest_snapshot.camera.width > 0 && latest_snapshot.camera.height > 0) {
            float scale_x = static_cast<float>(DEFAULT_WINDOW_WIDTH) / latest_snapshot.camera.width;
            float scale_y = static_cast<float>(DEFAULT_WINDOW_HEIGHT) / latest_snapshot.camera.height;
            
            render_storage.get_scene().render(latest_snapshot.camera, scale_x, scale_y);
            
            for (MapComponent &component : latest_snapshot.map.components)
                render_storage.get_map_drawer().render_component(component,
                    latest_snapshot.map.style, latest_snapshot.camera, scale_x, scale_y);
             
            for (BoxSnapshot &box : latest_snapshot.boxes)
                render_storage.get_box_item().render(box, latest_snapshot.camera, scale_x, scale_y);

            for (Position &position : latest_snapshot.map.gun_spawns)
                render_storage.get_map_drawer().render_spawn_in_map(position, latest_snapshot.camera, scale_x, scale_y);

            for (DuckSnapshot &duck_snapshot : latest_snapshot.ducks)
                render_storage.get_duck().render(duck_snapshot, frame_ticks, latest_snapshot.camera, scale_x, scale_y);

            for (GunNoEquippedSnapshot &gun : latest_snapshot.guns)
                render_storage.get_item().render(gun, latest_snapshot.camera, scale_x, scale_y);

            for (ProjectileSnapshot &projectile : latest_snapshot.projectiles)
                render_storage.get_projectile_drawer().render(projectile, latest_snapshot.camera, scale_x, scale_y);

            for (ExplosionSnapshot &explosion : latest_snapshot.explosions)
                render_storage.get_explosion().render(explosion, frame_ticks, latest_snapshot.camera, scale_x, scale_y);

            // for (SoundSnapshot &sound_snapshot : latest_snapshot.sounds)
            //     music_box.play_sound(sound_snapshot);
        }
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
