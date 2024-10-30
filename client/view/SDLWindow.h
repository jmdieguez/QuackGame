
#include <SDL2pp/SDL2pp.hh>

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