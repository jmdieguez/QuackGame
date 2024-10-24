#include "controller/game.h"

#define DEFAULT_WINDOW_WIDTH 480
#define DEFAULT_WINDOW_HEIGHT 640
#define WINDOW_TITTLE "Duck Game"
#define DUCK_PATH "assets/duck.png"

int main()
{
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    SDL2pp::Window window(WINDOW_TITTLE,
                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                          DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_WIDTH,
                          SDL_WINDOW_RESIZABLE);
    SDL2pp::Renderer duck_renderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL2pp::Texture duck_sprites(duck_renderer, SDL2pp::Surface(DUCK_PATH).SetColorKey(true, 0));
    Game game(duck_renderer, duck_sprites);
    game.run();
}