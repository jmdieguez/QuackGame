#include "editor.h"

#define N_ARGS 2

inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

int main(int argc, char *argv[]) {
    if (argc == N_ARGS) {
        std::string out_file = argv[1];
        if (out_file.ends_with(".yaml")) {
            SDL sdl(SDL_INIT_VIDEO);
            SDLTTF ttf;
            Window window("Quack Game Editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);
            Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
            Editor editor(renderer, out_file);
            return editor.run();
        }
    } else {
        std::cout << "Please specify a valid name for your map destination file.\n";
        std::cout << "Usage: ./quack_game_editor <map_name>.yaml \n";
        return ERROR;
    }
}
