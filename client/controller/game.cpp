#include "game.h"
#include "../model/receiver.h"
#include "../model/sender.h"

#define MAX_MESSAGES_QUEUE_RECEIVER 100000
#define MAX_MESSAGES_QUEUE_SENDER 100000

#define DEFAULT_WINDOW_WIDTH 480
#define DEFAULT_WINDOW_HEIGHT 640
#define IMAGE_WIDTH 32
#define IMAGE_HEIGHT 32
#define IMAGE_RECT_WIDTH 64
#define IMAGE_RECT_HEIGHT 64
#define FIRST_RUN_PHASE 1
#define POS_INIT_X_IMAGE 1
#define POS_INIT_Y_IMAGE 8

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

void Game::update_run_phase_and_position(unsigned int frame_ticks, unsigned int frame_delta)
{
    (void)frame_ticks;
    (void)frame_delta;
    // if (!game_context.get_is_running())
    // {
    //     run_phase = FIRST_RUN_PHASE;
    //     return;
    // }
    // position += frame_delta * 0.2 * (game_context.get_is_right_direction() ? 1 : -1);

    // run_phase = (frame_ticks / 100) % 5 + 1;
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

void Game::set_xy(int &src_x, int &src_y)
{
    (void)src_x;
    (void)src_y;
    // if (game_context.get_is_running())
    //     src_x = IMAGE_WIDTH * run_phase;

    // if (game_context.get_is_bent_down())
    // {
    //     src_x = IMAGE_WIDTH * 5;
    //     src_y = POS_INIT_Y_IMAGE + IMAGE_HEIGHT;
    // }

    // if (game_context.get_is_running() && game_context.get_is_bent_down())
    // {
    //     src_x = IMAGE_WIDTH;
    //     src_y = POS_INIT_Y_IMAGE + IMAGE_HEIGHT * 2;
    // }
}

void Game::update_renderer()
{
    duck_renderer.Clear();
    set_renderer();
    duck_renderer.Present();
}

void Game::set_renderer()
{
    Snapshot snapshot;
    if (!queue_receiver.try_pop(snapshot))
        return;
    for (DuckSnapshot duck : snapshot.ducks)
    {
        int src_x = POS_INIT_X_IMAGE, src_y = POS_INIT_Y_IMAGE;
        set_xy(src_x, src_y);
        SDL_Rect src_rect = {src_x, src_y, IMAGE_WIDTH, IMAGE_HEIGHT};
        SDL_Rect dst_rect = {duck.position.pos_x, duck.position.pos_y - IMAGE_HEIGHT, IMAGE_RECT_WIDTH, IMAGE_RECT_HEIGHT};
        // SDL_RendererFlip flip = game_context.get_is_right_direction() ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
        SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(duck_renderer.Get(), duck_sprites.Get(), &src_rect, &dst_rect, 0.0, nullptr, flip);
    }
}

void Game::step([[maybe_unused]] unsigned int current_step)
{
    (void)current_step;
    unsigned int frame_ticks = SDL_GetTicks();
    unsigned int frame_delta = frame_ticks - prev_ticks;
    prev_ticks = frame_ticks;

    get_and_execute_events();
    update_run_phase_and_position(frame_ticks, frame_delta);
    update_renderer();
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Game::Game(SDL2pp::Renderer &renderer, SDL2pp::Texture &sprites, const char *host, const char *port)
    : keep_running(true),
      run_phase(1),
      prev_ticks(SDL_GetTicks()),
      constant_rate_loop(keep_running, [this](unsigned int step)
                         { this->step(step); }),
      duck_renderer(renderer),
      duck_sprites(sprites),
      queue_receiver(MAX_MESSAGES_QUEUE_RECEIVER),
      queue_sender(MAX_MESSAGES_QUEUE_SENDER),
      input(queue_sender),
      game_context(queue_sender),
      socket(host, port) {}

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
