#include "editor.h"

int main() {
    SDL sdl(SDL_INIT_VIDEO);
    SDLTTF ttf;
    Window window("Quack Game Editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);
    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
    std::string out_file = "map.yaml"; // Leer como parámetro
    Editor editor(renderer, out_file);
    return editor.run();
}
