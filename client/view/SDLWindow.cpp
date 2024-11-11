#include "SDLWindow.h"

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720
#define WINDOW_TITTLE "Quack Game"

SDLWindow::SDLWindow()
    : sdl(SDL_INIT_VIDEO), window(WINDOW_TITTLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT,
                                  SDL_WINDOW_RESIZABLE),
      renderer(window, -1, SDL_RENDERER_ACCELERATED)
{
}

SDL2pp::Renderer &SDLWindow::get_renderer()
{
    return renderer;
}

SDLWindow::~SDLWindow()
{
}
