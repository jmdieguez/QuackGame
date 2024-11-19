#include "mapdrawer.h"

#define TILESETS "/var/quackgame/tiles.png"

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

void MapDrawer::load_dimensions_and_tileset()
{
    YAML::Node root = YAML::LoadFile(DIMENSIONS_FILE);
    for (const auto &dim : root["components"])
    {
        Component type = dim["type"].as<Component>();
        uint16_t dim_x = dim["dim_x"].as<uint16_t>();
        uint16_t dim_y = dim["dim_y"].as<uint16_t>();
        dimensions.emplace(type, std::make_pair(dim_x * TILE_SIZE, dim_y * TILE_SIZE));
    }

    int n_tilesets = 5;

    for (uint8_t i = 0; i < n_tilesets; i++)
        tilesets.emplace(i, std::make_unique<Tileset>(i, renderer, all_tilesets_texture));
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

MapDrawer::MapDrawer(SDL2pp::Renderer &renderer) : Renderer(renderer),
                                                   all_tilesets_texture(std::make_shared<SDL2pp::Texture>(renderer, TILESETS))
{
    load_dimensions_and_tileset();
}

void MapDrawer::render_spawn_in_map(Position &p)
{
    SDL2pp::Texture &texture = get_texture(TextureFigure::Spawn_T);
    int width = texture.GetWidth();
    int height = texture.GetHeight();
    SDL_Rect src_rect = {0, 0, width, height};
    int x = (p.x * TILE_SIZE) + ((TILE_SIZE - width) / 2);
    int y = (p.y * TILE_SIZE) + (TILE_SIZE - height);
    SDL_Rect dst_rect = {x, y, width, height};
    renderer.Copy(texture, src_rect, dst_rect);
}

void MapDrawer::render_component(MapComponent &component, uint16_t &style)
{
    std::unique_ptr<Tileset> &tileset = tilesets[style];
    std::shared_ptr<SDL2pp::Texture> &texture = tileset->textures[component.type];
    uint8_t dim_x = dimensions[component.type].first;
    uint8_t dim_y = dimensions[component.type].second;
    SDL_Rect src_rect = {0, 0, dim_x, dim_y};
    SDL_Rect dst_rect = {component.x * TILE_SIZE, component.y * TILE_SIZE, dim_x, dim_y};
    renderer.Copy(*texture, src_rect, dst_rect);
}

MapDrawer::~MapDrawer()
{
}