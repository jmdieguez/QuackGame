#include <iostream>
#include <exception>
#include <string>

#include <SDL2pp/SDL2pp.hh>

#define DEFAULT_WINDOW_WIDTH 480
#define DEFAULT_WINDOW_HEIGHT 640
#define IMAGE_WIDTH 32
#define IMAGE_HEIGHT 32
#define IMAGE_RECT_WIDTH 64
#define IMAGE_RECT_HEIGHT 64
#define RED 255, 0, 0
#define DUCK_PATH "./assets/duck.png"

int main()
try
{
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);

    SDL2pp::SDLTTF ttf;

    SDL2pp::Window window("SDL2pp demo",
                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                          DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_WIDTH,
                          SDL_WINDOW_RESIZABLE);

    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL2pp::Texture sprites(renderer, SDL2pp::Surface(DUCK_PATH)
                                          .SetColorKey(true, 0));
    sprites.SetColorMod(RED);
    bool right_direction = true;
    bool is_running = false;
    bool is_bent_down = false;
    int run_phase = 1;
    float position = 0.0;

    unsigned int prev_ticks = SDL_GetTicks();

    while (true)
    {
        unsigned int frame_ticks = SDL_GetTicks();
        unsigned int frame_delta = frame_ticks - prev_ticks;
        prev_ticks = frame_ticks;

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                return 0;
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                case SDLK_q:
                    return 0;
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

        if (position > renderer.GetOutputWidth())
            position = -50;
        else if (position < -50)
            position = renderer.GetOutputWidth();

        int vcenter = renderer.GetOutputHeight() / 2;
        renderer.Clear();

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
        SDL_RenderCopyEx(renderer.Get(), sprites.Get(), &src_rect, &dst_rect, 0.0, nullptr, flip);

        renderer.Present();

        SDL_Delay(1);
    }
    return 0;
}
catch (std::exception &e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}