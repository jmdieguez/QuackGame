#include "SDLInitializer.h"

#define WINDOW_TITTLE "Quack Game"

SDLInitializer::SDLInitializer()
    : sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO), window(WINDOW_TITTLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                                   DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT,
                                                   SDL_WINDOW_RESIZABLE),
      renderer(window, -1, SDL_RENDERER_ACCELERATED),
      mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096)
{
}

SDL2pp::Renderer &SDLInitializer::get_renderer()
{
    return renderer;
}

SDL2pp::Mixer &SDLInitializer::get_mixer()
{
    return mixer;
}

SDLInitializer::~SDLInitializer()
{
}
