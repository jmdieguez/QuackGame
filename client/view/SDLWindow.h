#ifndef WRAPPER_SDL_WINDOW_H
#define WRAPPER_SDL_WINDOW_H

#include <SDL2pp/SDL2pp.hh>

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720

class SDLWindow
{
private:
    SDL2pp::SDL sdl;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;

public:
    SDLWindow();
    SDL2pp::Renderer &get_renderer();
    ~SDLWindow();
};

#endif // WRAPPER_SDL_WINDOW_H
