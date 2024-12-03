#include "game.h"
#include "../../common/config.h"

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
    {
        if (is_showing_table)
            return;
        handle_event(event);
    }
}

void Game::update_renderer(int frame_ticks)
{
    // if (true)
    // {
    //     Ejemplos para mostrar en la tabla
    //     UserTable user1, user2, user3, user4, user5, user6, user7, user8, user9, user10;
    //     user1.color_name = "Rojo";
    //     user1.round_wins = 5;

    //     user2.color_name = "Azul";
    //     user2.round_wins = 3;

    //     user3.color_name = "Verde";
    //     user3.round_wins = 8;

    //     user4.color_name = "Amarillo";
    //     user4.round_wins = 6;

    //     user5.color_name = "Naranja";
    //     user5.round_wins = 4;

    //     user6.color_name = "Rosa";
    //     user6.round_wins = 2;

    //     user7.color_name = "Morado";
    //     user7.round_wins = 7;

    //     user8.color_name = "Cyan";
    //     user8.round_wins = 9;

    //     user9.color_name = "Blanco";
    //     user9.round_wins = 1;

    //     user10.color_name = "Negro";
    //     user10.round_wins = 3;

    //     std::vector<UserTable> user_list = {user1, user2, user3, user4, user5, user6, user7, user8, user9, user10};
    //     UserTableSnapshot snapshot_table(user_list);

    //     Codigo  de la tabla (ubicarla donde de va ir)

    //     initializer.get_renderer().Clear();
    //     render_storage.get_scene().render();
    //     table_screen.render(font, snapshot_table);

    //     initializer.get_renderer().Present();
    //     return;
    // }

    set_renderer(frame_ticks);
    initializer.get_renderer().Present();
}

void Game::process_projectile(ProjectileSnapshot &projectile, Snapshot &snapshot, float scale_x, float scale_y)
{
    if (!mute_effect && projectile.texture != TextureFigure::None && projectile.texture != TextureFigure::GrenadeFigure && projectile.texture != TextureFigure::BananaFigure && projectile.texture != TextureFigure::BananaThrown)
        projectile.texture == TextureFigure::LaserRifleBullet ? sound_storage.get_projectile_laser_sound().sound(projectile.id) : sound_storage.get_projectile_sound().sound(projectile.id);
    render_storage.get_projectile_drawer().render(projectile, snapshot.camera, scale_x, scale_y);
}

void Game::process_explosion(ExplosionSnapshot &explosion, int frame_ticks, Snapshot &snapshot, float scale_x, float scale_y)
{
    if (explosion.texture == TextureFigure::None)
        return;
    if (!mute_effect)
        sound_storage.get_explosion_sound().sound(explosion.id);
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
        loading_screen.render(font, users);
    }
    if (received_snapshot)
    {

        if (latest_snapshot.camera.width > 0 && latest_snapshot.camera.height > 0)
        {
            initializer.get_renderer().Clear();
            float scale_x = static_cast<float>(DEFAULT_WINDOW_WIDTH) / latest_snapshot.camera.width;
            float scale_y = static_cast<float>(DEFAULT_WINDOW_HEIGHT) / latest_snapshot.camera.height;

            render_storage.get_scene().render(latest_snapshot.camera, scale_x, scale_y);

            for (MapComponent &component : latest_snapshot.map.components)
                render_storage.get_map_drawer().render_component(component,
                                                                 latest_snapshot.map.style, latest_snapshot.camera, scale_x, scale_y);

            for (BoxSnapshot &box : latest_snapshot.boxes)
                render_storage.get_box_item().render(box, latest_snapshot.camera, scale_x, scale_y);

            for (ProjectileSnapshot &projectile : latest_snapshot.projectiles)
                process_projectile(projectile, latest_snapshot, scale_x, scale_y);

            for (ExplosionSnapshot &explosion : latest_snapshot.explosions)
                process_explosion(explosion, frame_ticks, latest_snapshot, scale_x, scale_y);

            for (Position &position : latest_snapshot.map.gun_spawns)
                render_storage.get_map_drawer().render_spawn_in_map(position, latest_snapshot.camera, scale_x, scale_y);

            unsigned ducks_alive = 0;
            for (DuckSnapshot &duck_snapshot : latest_snapshot.ducks)
            {   
                if (duck_snapshot.status.is_alive)
                    ducks_alive++;    
                render_storage.get_duck().render(duck_snapshot, frame_ticks, latest_snapshot.camera, scale_x,
                                                 scale_y);
            }
            for (GunNoEquippedSnapshot &gun : latest_snapshot.guns)
                render_storage.get_item().render(gun, latest_snapshot.camera, scale_x, scale_y);

            for (ArmorSnapshot &armor : latest_snapshot.armors)
                render_storage.get_armor().render(armor, latest_snapshot.camera, scale_x, scale_y);
            
            if (ducks_alive <= 1) {
                SDL2pp::Texture text(initializer.get_renderer(), font.RenderText_Blended("THE NEXT ROUND IS ABOUT TO START...", WHITE));
                SDL_Rect text_src = {0, 0, text.GetWidth(), text.GetHeight()};
                SDL_Rect text_dst = {
                    (DEFAULT_WINDOW_WIDTH - text.GetWidth() / 2) / 2,
                    (DEFAULT_WINDOW_HEIGHT - text.GetHeight() / 2) / 4,
                    text.GetWidth() / 2,
                    text.GetHeight() / 2};
                initializer.get_renderer().Copy(text, text_src, text_dst);
            }

            if (latest_snapshot.is_ended)
            {
                winner = latest_snapshot.winning_color;
                keep_running = false;
                SDL_Quit();
            }
        }
        if (latest_snapshot.round != 0 && latest_snapshot.round != lastest_round_show_table && latest_snapshot.round % 5 == 0)
        {
            if (is_showing_table || finish_showing_table)
            {
                round = latest_snapshot.round;
                round_controller.handle_round_change(latest_snapshot.round, latest_snapshot.scores);
                return;
            }
            lastest_round_show_table = latest_snapshot.round;
            is_showing_table = false;
            finish_showing_table = true;
        }
    }
    sound_storage.clear_sounds();
}

void Game::step(unsigned int current_step)
{
    if (!mute_music)
        music.start(volume_music);
    unsigned int frame_ticks = current_step;
    get_and_execute_events();
    update_renderer(frame_ticks);
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Game::Game(Socket skt, std::vector<UserLobbyInfo> users)
    : keep_running(true),
      constant_rate_loop(keep_running, [this](unsigned int step)
                         { this->step(step); }),
      font(FONT_PATH, 32),
      loading_screen(initializer.get_renderer()),
      session(users),
      users(users),
      lastest_round_show_table(0),
      is_showing_table(false),
      finish_showing_table(true),
      render_storage(initializer.get_renderer()),
      round_controller(render_storage, initializer.get_renderer(), font, is_showing_table, finish_showing_table),
      sound_storage(initializer.get_mixer()),
      music(initializer.get_mixer()),
      mute_effect(Config::getInstance()["effect"]["mute"].as<bool>()),
      volume_music(Config::getInstance()["music"]["volume"].as<unsigned>()),
      mute_music(Config::getInstance()["music"]["mute"].as<bool>()),
      socket(std::move(skt))
{
}

void Game::run(std::string& winner)
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
    winner = this->winner;
}

Game::~Game() {}
