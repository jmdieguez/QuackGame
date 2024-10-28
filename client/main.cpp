#include "controller/game.h"

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720
#define WINDOW_TITTLE "Duck Game"
#define DUCK_PATH "assets/duck.png"

#define OK 0
#define ERROR 1
#define HOST 1
#define PORT 2
#define MIN_ARGS 3

int main(int argc, const char *argv[])
{

    if (argc != MIN_ARGS)
        return ERROR;

    try
    {
        SDL2pp::SDL sdl(SDL_INIT_VIDEO);
        SDL2pp::Window window(WINDOW_TITTLE,
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT,
                              SDL_WINDOW_RESIZABLE);
        SDL2pp::Renderer duck_renderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL2pp::Surface duck_surface(DUCK_PATH);
        SDL2pp::Texture duck_sprites(duck_renderer, duck_surface);
        SDL_FreeSurface(duck_surface.Get());

        const char *host = argv[HOST];
        const char *port = argv[PORT];

        Game game(duck_renderer, duck_sprites, host, port);
        game.run();

        return OK;
    }
    catch (const std::exception &err)
    {
        std::cerr << "Something went wrong and an exception was caught: " << err.what()
                  << std::endl;
        return ERROR;
    }
    catch (...)
    {
        std::cerr << "Something went wrong and an unknown exception was caught." << std::endl;
        return ERROR;
    }
    return OK;
}