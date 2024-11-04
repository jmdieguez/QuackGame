#ifndef SERVER_MAP_H
#define SERVER_MAP_H

#include "../../common/defs.h"
#include "../../common/snapshots.h"
#include "../../common/map.h"
#include "../../common/position.h"
#include "gun/cowboypistol.h"

#include <utility>
#include <yaml-cpp/yaml.h>

#define DIMENSIONS_FILE "dimensions.yaml"

class Map
{
private:
    MapConfig cfg;
    uint16_t style;
    uint16_t size_x;
    uint16_t size_y;
    uint16_t gun_id;
    std::vector<MapComponent> components;
    std::vector<bool> bit_map; // true: wall/ground. false: empty space
    std::map<Component, std::pair<uint8_t, uint8_t>> dimensions;
    std::map<uint8_t, std::shared_ptr<Gun>> guns;

    MapConfig load_yaml_config(const std::string &filename)
    {
        MapConfig config;
        YAML::Node root = YAML::LoadFile(filename);
        config.n_tiles_x = root["n_tiles_x"].as<uint16_t>();
        config.n_tiles_y = root["n_tiles_y"].as<uint16_t>();
        config.tileset_style = root["tileset"].as<uint16_t>();

        for (const auto &itemNode : root["items"])
        {
            uint16_t x = itemNode["x"].as<uint16_t>();
            uint16_t y = itemNode["y"].as<uint16_t>();
            Component component = itemNode["type"].as<Component>();
            config.components.push_back(MapComponent(x, y, component));
        }

        return config;
    }

    void initiate_components_dimensions()
    {
        YAML::Node root = YAML::LoadFile(DIMENSIONS_FILE);
        for (const auto &dim : root["components"])
        {
            Component type = dim["type"].as<Component>();
            uint16_t dim_x = dim["dim_x"].as<uint16_t>(); // n tiles
            uint16_t dim_y = dim["dim_y"].as<uint16_t>();
            dimensions.emplace(type, std::make_pair(dim_x, dim_y));
        }
    }

    void initiate_components()
    {
        for (const MapComponent &component : cfg.components)
        {
            std::pair<int, int> component_dimensions = dimensions[component.type];
            int x_pixels = component_dimensions.first * TILE_SIZE;
            int y_pixels = component_dimensions.second * TILE_SIZE;
            int start_x = component.x * TILE_SIZE;
            int start_y = component.y * TILE_SIZE;

            for (int i = 0; i < x_pixels; i++)
            {
                for (int j = 0; j < y_pixels; j++)
                {
                    int x_pos = start_x + i;
                    int y_pos = start_y + j;
                    int index = x_pos + (y_pos * size_x);
                    bit_map[index] = true;
                }
            }
        }
    }

public:
    Map(const std::string &map_file) : cfg(load_yaml_config(map_file)),
                                       style(cfg.tileset_style),
                                       size_x(cfg.n_tiles_x * TILE_SIZE),
                                       size_y(cfg.n_tiles_y * TILE_SIZE),
                                       gun_id(0),
                                       bit_map(size_x * size_y, false)
    {

        initiate_components_dimensions();
        initiate_components();
        // Eliminar una vez que se tengan los spawns de las armas
        guns.emplace(gun_id, std::make_shared<CowboyPistol>(190, 128));
        gun_id++;
    }

    ~Map() {}

    MapSnapshot get_status() { return MapSnapshot(style, size_x, size_y, components); }

    bool validate_coordinate(Position &p)
    {
        return (p.pos_x < size_x) && (p.pos_y < size_y) && !has_something_in(p);
    }

    bool has_something_in(Position &p)
    {
        return bit_map[p.pos_x + (p.pos_y * size_x)];
    }

    std::map<uint8_t, std::shared_ptr<Gun>> &get_guns()
    {
        return guns;
    }

    void remove_gun(uint16_t id)
    {
        guns.erase(id);
    }
};

#endif // SERVER_MAP_H
