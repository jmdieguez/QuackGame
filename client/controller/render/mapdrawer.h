#ifndef MAP_DRAWER_H
#define MAP_DRAWER_H

#include "renderer.h"
#include "../ui/tileset.h"
#include "../../../common/snapshots.h"

class MapDrawer : private Renderer
{
private:
    std::shared_ptr<SDL2pp::Texture> all_tilesets_texture;
    std::map<uint8_t, std::unique_ptr<Tileset>> tilesets;
    std::map<Component, std::pair<uint8_t, uint8_t>> dimensions;

    void load_dimensions_and_tileset();

public:
    explicit MapDrawer(SDL2pp::Renderer &renderer);
    void render_spawn_in_map(Position &p);
    void render_component(MapComponent &component, uint16_t &style);
    ~MapDrawer();
};

#endif // MAP_DRAWER_H