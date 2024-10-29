#include "editor.h"

int main() {
    SDL sdl(SDL_INIT_VIDEO);
    SDLTTF ttf;
    Window window("Quack Game Editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);
    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
    Editor editor(renderer);
    return editor.run();
}
