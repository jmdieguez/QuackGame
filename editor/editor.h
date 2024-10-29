#ifndef EDITOR_H
#define EDITOR_H

#include <memory>
#include <map>

#include "tiles.h"
#include "tileset.h"
#include "grid.h"
#include "save_button.h"

#define TILESETS "assets/tiles.png"
#define N_TILESETS 5

class Editor {
private:
    Renderer &renderer;
    Font font;
    bool running = true;
    bool save_on_exit = false;
    uint8_t current_style = 1;
    std::shared_ptr<Texture> all_tilesets;
    std::unique_ptr<Tileset> current_tileset;
    std::string selected_texture;
    const int w_width = 1920;
    const int w_height = 1080;
    Grid tiles_grid;
    Tiles tiles;
    SaveButton s_button;
    std::string out_file;
public:
    explicit Editor(Renderer &r, std::string &path) : renderer(r), font(FONT_PATH, 16), 
        all_tilesets(std::make_shared<Texture>(renderer, TILESETS)), s_button(r), out_file(path) {
        current_tileset = std::make_unique<Tileset>(current_style, renderer, all_tilesets); 
    }

    ~Editor() {}

    int run();
    void save();
    void draw_tiles();
    void draw_textures();
    void handle_event(const SDL_Event& event);
};

#endif // EDITOR_H
