#ifndef EDITOR_H
#define EDITOR_H

#include <memory>
#include <map>

#include "tiles.h"
#include "tileset.h"
#include "grid.h"

#define TILESETS "assets/tiles.png"
#define FONT_PATH "assets/04B_30.TTF"
#define N_TILESETS 5

class Editor {
private:
    Renderer &renderer;
    Font font;
    uint8_t current_style = 0;
    std::shared_ptr<Texture> all_tilesets;
    std::unique_ptr<Tileset> current_tileset;
    std::string selected_texture;
    const int w_width = 1920;
    const int w_height = 1080;
    Grid tiles_grid;
    Tiles tiles;

public:
    explicit Editor(Renderer &r) : renderer(r), font(FONT_PATH, 16), all_tilesets(std::make_shared<Texture>(renderer, TILESETS)) {
        current_tileset = std::make_unique<Tileset>(current_style, renderer, all_tilesets); 
    }

    ~Editor() {}

    int run();
    void draw_tiles();
    void draw_grid();
    void draw_textures();
    void handle_event(const SDL_Event& event);
};

#endif // EDITOR_H
