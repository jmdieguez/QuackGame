#include "game.h"

#define MAX_MESSAGES_QUEUE_RECEIVER 100000
#define MAX_MESSAGES_QUEUE_SENDER 100000

#define DEFAULT_WINDOW_WIDTH 480
#define DEFAULT_WINDOW_HEIGHT 640
#define IMAGE_WIDTH 32
#define IMAGE_HEIGHT 32
#define IMAGE_RECT_WIDTH 64
#define IMAGE_RECT_HEIGHT 64

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

void Game::step([[maybe_unused]] unsigned int current_step)
{
    (void)current_step;
    unsigned int frame_ticks = SDL_GetTicks();
    unsigned int frame_delta = frame_ticks - prev_ticks;
    prev_ticks = frame_ticks;
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            keep_running = false;

        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
            case SDLK_q:
                keep_running = false;
                break;
            case SDLK_a:
                right_direction = false;
                is_running = true;
                break;
            case SDLK_d:
                right_direction = true;
                is_running = true;
                break;
            case SDLK_s:
                is_bent_down = true;
                break;
            }
        }
        else if (event.type == SDL_KEYUP)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_a:
            case SDLK_d:
                is_running = false;
                break;
            case SDLK_s:
                is_bent_down = false;
            }
        }
    }

    if (is_running)
    {
        if (right_direction)
            position += frame_delta * 0.2;
        else
            position -= frame_delta * 0.2;
        run_phase = (frame_ticks / 100) % 5 + 1;
    }
    else
        run_phase = 1;

    if (position > duck_renderer.GetOutputWidth())
        position = -50;
    else if (position < -50)
        position = duck_renderer.GetOutputWidth();

    int vcenter = duck_renderer.GetOutputHeight() / 2;
    duck_renderer.Clear();

    int src_x = 1, src_y = 8;
    if (is_running)
        src_x = IMAGE_WIDTH * run_phase;

    if (is_bent_down)
    {
        src_x = IMAGE_WIDTH * 5;
        src_y = 8 + IMAGE_HEIGHT;
    }

    if (is_running && is_bent_down)
    {
        src_x = IMAGE_WIDTH;
        src_y = 8 + IMAGE_HEIGHT * 2;
    }

    SDL_Rect src_rect = {src_x, src_y, IMAGE_WIDTH, IMAGE_HEIGHT};
    SDL_Rect dst_rect = {(int)position, vcenter - 50, IMAGE_RECT_WIDTH, IMAGE_RECT_HEIGHT};

    SDL_RendererFlip flip = right_direction ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(duck_renderer.Get(), duck_sprites.Get(), &src_rect, &dst_rect, 0.0, nullptr, flip);

    duck_renderer.Present();
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Game::Game(SDL2pp::Renderer &renderer, SDL2pp::Texture &sprites)
    : keep_running(true),
      right_direction(true),
      is_running(false),
      is_bent_down(false),
      run_phase(1),
      position(0.0),
      prev_ticks(SDL_GetTicks()),
      constant_rate_loop(keep_running, [this](unsigned int step)
                         { this->step(step); }),
      duck_renderer(renderer),
      duck_sprites(sprites),
      queue_receiver(MAX_MESSAGES_QUEUE_RECEIVER),
      queue_sender(MAX_MESSAGES_QUEUE_SENDER) {}

void Game::run()
{
    // network.run();
    constant_rate_loop.execute();
    // network.join();
}

Game::~Game() {}
