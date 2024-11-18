#ifndef WRAPPER_SDL_WINDOW_H
#define WRAPPER_SDL_WINDOW_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Mixer.hh>

#include "../../ui/defs.h"

class SDLInitializer
{
private:
    SDL2pp::SDL sdl;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;
    SDL2pp::Mixer mixer;
    SDL2pp::SDLTTF ttf;
public:
    SDLInitializer();
    SDL2pp::Renderer &get_renderer();
    SDL2pp::Mixer &get_mixer();
    ~SDLInitializer();
};

#endif // WRAPPER_SDL_WINDOW_H
