#include <iostream>
#include <exception>
#include <algorithm>
#include <string>

#include <SDL2pp/SDL2pp.hh>

#define DEFAULT_WINDOW_WIDTH 480
#define DEFAULT_WINDOW_HEIGHT 640
#define IMAGE_WIDTH 32
#define IMAGE_HEIGHT 32
#define IMAGE_RECT_WIDTH 64
#define IMAGE_RECT_HEIGHT 64
#define ASSETS_PATH "./assets"

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

    SDL2pp::Texture sprites(renderer, SDL2pp::Surface(ASSETS_PATH "/duck.png")
                                          .SetColorKey(true, 0));

    bool is_running = false;
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
                case SDLK_RIGHT:
                    is_running = true;
                    break;
                }
            }
            else if (event.type == SDL_KEYUP)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    is_running = false;
                    break;
                }
            }
        }

        if (is_running)
        {
            position += frame_delta * 0.2;
            run_phase = (frame_ticks / 100) % 5 + 1;
        }
        else
            run_phase = 1;

        if (position > renderer.GetOutputWidth())
            position = -50;

        int vcenter = renderer.GetOutputHeight() / 2;
        renderer.Clear();

        int src_x = 1, src_y = 8;
        if (is_running)
            src_x = IMAGE_WIDTH * run_phase;

        renderer.Copy(
            sprites,
            SDL2pp::Rect(src_x, src_y, IMAGE_WIDTH, IMAGE_HEIGHT),
            SDL2pp::Rect((int)position, vcenter - 50, IMAGE_RECT_WIDTH, IMAGE_RECT_HEIGHT));

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