#include "controller/game.h"

#define DEFAULT_WINDOW_WIDTH 480
#define DEFAULT_WINDOW_HEIGHT 640
#define WINDOW_TITTLE "Duck Game"
#define DUCK_PATH "assets/duck.png"

int main(int argc, const char* argv[])
{
   try {

        SDL2pp::SDL sdl(SDL_INIT_VIDEO);
        SDL2pp::Window window(WINDOW_TITTLE,
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_WIDTH,
                              SDL_WINDOW_RESIZABLE);
        SDL2pp::Renderer duck_renderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL2pp::Texture duck_sprites(duck_renderer, SDL2pp::Surface(DUCK_PATH).SetColorKey(true, 0));

       const char* hostname = NULL;
       const char* servname = NULL;

       if (argc == 2) {
           hostname = argv[1];
       } else if (argc == 3) {
           hostname = argv[1];
           servname = argv[2];
       } else {
           std::cerr << "Bad program call. Expected " << argv[0] << " <hostname> [<servname>]\n";
           return 1;
       }


        Game game(duck_renderer, duck_sprites, servname, hostname);
        game.run();
        return 0;

   } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what()
                  << std::endl;
        return 1;
   } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught." << std::endl;
        return 1;
   }
}