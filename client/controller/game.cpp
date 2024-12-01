#include "game.h"
#include "render/transitionmanager.h"

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
    set_renderer(frame_ticks);
    initializer.get_renderer().Present();
}

void Game::process_projectile(ProjectileSnapshot &projectile, Snapshot &snapshot, float scale_x, float scale_y)
{
    if (projectile.texture != TextureFigure::None && projectile.texture != TextureFigure::GrenadeFigure)
        music_storage.get_projectile_sound().sound(projectile.id);
    render_storage.get_projectile_drawer().render(projectile, snapshot.camera, scale_x, scale_y);
}

void Game::process_explosion(ExplosionSnapshot &explosion, int frame_ticks, Snapshot &snapshot, float scale_x, float scale_y)
{
    if (explosion.texture == TextureFigure::None)
        return;
    music_storage.get_explosion_sound().sound(explosion.id);
    render_storage.get_explosion().render(explosion, frame_ticks, snapshot.camera, scale_x, scale_y);
}

void Game::set_renderer(int frame_ticks)
{
    Snapshot snapshot, latest_snapshot;
    auto &queue = session.get_queue_receiver();

    bool received_snapshot = false;
    while (queue.try_pop(snapshot))
    {
        started = true;
        latest_snapshot = snapshot;
        received_snapshot = true;
    }

    if (!started)
    {
        initializer.get_renderer().Clear();
        render_storage.get_scene().render();
        loading_screen.render();
    }

    if (received_snapshot)
    {
        if (latest_snapshot.camera.width > 0 && latest_snapshot.camera.height > 0)
        {
            if (round != latest_snapshot.round) {
                TransitionManager transitionManager(initializer.get_renderer());
                round = latest_snapshot.round;
                transitionManager.fadeTransition(latest_snapshot.round);
            }

            initializer.get_renderer().Clear();
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
                process_projectile(projectile, latest_snapshot, scale_x, scale_y);

            for (ExplosionSnapshot &explosion : latest_snapshot.explosions)
                process_explosion(explosion, frame_ticks, latest_snapshot, scale_x, scale_y);

            for (ArmorSnapshot &armor : latest_snapshot.armors)
                render_storage.get_armor().render(armor, latest_snapshot.camera, scale_x, scale_y);
            if (latest_snapshot.is_ended) {
                victory = snapshot.game_result == GameResult::VICTORY;
                std::cout << victory << std::endl;

                initializer.get_renderer().Clear();
                keep_running = false;
                SDL_Quit();
            }
        }
    }
    music_storage.clear_sounds();
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
      render_storage(initializer.get_renderer()),
      music_storage(initializer.get_mixer()),
      socket(std::move(skt))
{
}

bool Game::run()
{
    Receiver receiver(socket, session.get_queue_receiver());
    Sender sender(socket, session.get_queue_sender());
    receiver.start();
    sender.start();
    constant_rate_loop.execute();
    receiver.stop();
    sender.stop();
    socket.shutdown(2);
    socket.close();
    receiver.join();
    sender.join();
    return victory;
}

Game::~Game() {}
