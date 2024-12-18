#ifndef EDITOR_H
#define EDITOR_H

#include <memory>
#include <map>

#include "common/map.h"
#include "common/tiles.h"
#include "ui/tileset.h"
#include "grid.h"
#include "buttons.h"

#ifdef GLOBAL_INSTALL
    #define SINGLE_DUCK_TEXTURE "/var/quackgame/duck/single_duck.png"
    #define SPAWN_TEXTURE "/var/quackgame/spawn.png"
    #define BOX_TEXTURE "/var/quackgame/box.png"
    #define TILESETS "/var/quackgame/tiles.png"
#else // LOCAL_INSTALL
    #define SINGLE_DUCK_TEXTURE "assets/duck/single_duck.png"
    #define SPAWN_TEXTURE "assets/spawn.png"
    #define BOX_TEXTURE "assets/box.png"
    #define TILESETS "assets/tiles.png"
#endif

#define N_TILESETS 5

enum class EditorState {
    IDLE = 0,
    CREATING_COMPONENTS,
    CLEANING_TILES,
    CREATING_GUN_SPAWNS,
    CREATING_DUCK_SPAWNS,
    CREATING_BOXES
};

class Editor
{
private:
    Renderer &renderer;
    Font font;
    bool running = true;
    bool save_on_exit = false;
    EditorState state;
    uint8_t current_style = 1;
    std::map<Component, std::string> titles;
    std::shared_ptr<Texture> all_tilesets;
    std::unique_ptr<Tileset> current_tileset;
    Texture box_texture;
    Texture gun_spawn_texture;
    Texture duck_texture;
    Component selected_texture;
    const int w_width = 1920;
    const int w_height = 1080;
    Grid tiles_grid;
    Tiles tiles;
    SaveButton save_button;
    DuckSpawnButton duck_button;
    GunSpawnButton gun_button;
    DeleteButton delete_button;
    BoxButton box_button;
    std::string out_file;
public:
    explicit Editor(Renderer &r, std::string &path) : renderer(r), font(FONT_PATH, 16),
                                                      all_tilesets(std::make_shared<Texture>(renderer, TILESETS)),
                                                      box_texture(renderer, BOX_TEXTURE),
                                                      gun_spawn_texture(renderer, SPAWN_TEXTURE),
                                                      duck_texture(renderer, SINGLE_DUCK_TEXTURE),
                                                      save_button(r),
                                                      duck_button(r),
                                                      gun_button(r),
                                                      delete_button(r),
                                                      box_button(r),
                                                      out_file(path)
    {
        current_tileset = std::make_unique<Tileset>(current_style, renderer, all_tilesets);

        titles = {
            {Component::BIG_WALL, "BIG WALL"},
            {Component::BIG_WALL_GROUND, "BIG WALL GROUND"},
            {Component::BIG_WALL_BASE, "BIG WALL BASE"},
            {Component::LONG_GROUND, "LONG GROUND"},
            {Component::SINGLE_GROUND, "SINGLE GROUND"},
            {Component::SLIM_WALL, "SLIM WALL"}
        };
    }

    ~Editor() {}

    int run();
    void save();
    void draw_tiles();
    void draw_textures();
    void unselect();
    void handle_selection(const SDL_Point &mousePos);
    void handle_event(const SDL_Event &event);
};

#endif // EDITOR_H
