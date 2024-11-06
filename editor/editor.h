#ifndef EDITOR_H
#define EDITOR_H

#include <memory>
#include <map>

#include "../common/map.h"
#include "../ui/tiles.h"
#include "../ui/tileset.h"
#include "grid.h"
#include "save_button.h"

#define TILESETS "../var/quackgame/tiles.png"
#define N_TILESETS 5

class Editor
{
private:
    Renderer &renderer;
    Font font;
    bool running = true;
    bool save_on_exit = false;
    uint8_t current_style = 1;
    std::map<Component, std::string> titles;
    std::shared_ptr<Texture> all_tilesets;
    std::unique_ptr<Tileset> current_tileset;
    Component selected_texture;
    const int w_width = 1920;
    const int w_height = 1080;
    Grid tiles_grid;
    Tiles tiles;
    SaveButton s_button;
    std::string out_file;

public:
    explicit Editor(Renderer &r, std::string &path) : renderer(r), font(FONT_PATH, 16),
                                                      all_tilesets(std::make_shared<Texture>(renderer, TILESETS)), s_button(r), out_file(path)
    {
        current_tileset = std::make_unique<Tileset>(current_style, renderer, all_tilesets);

        titles = {
            {Component::BIG_WALL, "BIG WALL"},
            {Component::BIG_WALL_GROUND, "BIG WALL GROUND"},
            {Component::BIG_WALL_BASE, "BIG WALL BASE"},
            {Component::LONG_GROUND, "LONG GROUND"},
            {Component::SINGLE_GROUND, "SINGLE GROUND"},
            {Component::SLIM_WALL, "SLIM WALL"}};
    }

    ~Editor() {}

    int run();
    void save();
    void draw_tiles();
    void draw_textures();
    void handle_event(const SDL_Event &event);
};

#endif // EDITOR_H
