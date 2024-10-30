#ifndef SERVER_MAP_H
#define SERVER_MAP_H

#include "../../common/defs.h"
#include "../../common/snapshots.h"
#include "../../common/map.h"

#include <utility>
#include <yaml-cpp/yaml.h>

#define DIMENSIONS_FILE "dimensions.yaml"

class Map {
private:
    MapConfig cfg;
    uint16_t style;
    uint16_t size_x;
    uint16_t size_y;
    std::vector<MapComponent> components;
    std::vector<bool> bit_map; // true: wall/ground. false: empty space
    std::map<Component, std::pair<uint8_t, uint8_t>> dimensions; 

    MapConfig load_yaml_config(const std::string& filename) {
        MapConfig config;
        YAML::Node root = YAML::LoadFile(filename);
        config.n_tiles_x = root["n_tiles_x"].as<uint16_t>();
        config.n_tiles_y = root["n_tiles_y"].as<uint16_t>();
        config.tileset_style = root["tileset"].as<uint16_t>();

        for (const auto& itemNode : root["items"]) {
            uint16_t x = itemNode["x"].as<uint16_t>();
            uint16_t y = itemNode["y"].as<uint16_t>();
            Component component = itemNode["type"].as<Component>();
            config.components.push_back(MapComponent(x, y, component));
        }

        return config;
    }

public:
    Map(const std::string &map_file) : cfg(load_yaml_config(map_file)),
                                style(cfg.tileset_style), 
                                size_x(cfg.n_tiles_x * TILE_SIZE), 
                                size_y(cfg.n_tiles_y * TILE_SIZE),
                                bit_map(size_x * size_y, false) {
        
        YAML::Node root = YAML::LoadFile(DIMENSIONS_FILE);
        for (const auto& dim : root["components"]) {
            Component type = dim["type"].as<Component>();
            uint16_t dim_x = dim["dim_x"].as<uint16_t>(); // n tiles
            uint16_t dim_y = dim["dim_y"].as<uint16_t>();
            dimensions.emplace(type, std::make_pair(dim_x, dim_y));
        }

        for (const MapComponent& component : cfg.components) {
            std::pair<int, int> component_dimensions = dimensions[component.type];
            for (int i = component.x; i < component.x + component_dimensions.first; i++) {
                for (int j = component.y; j < component.y + component_dimensions.second; j++) {
                    bit_map[i + (j * TILE_SIZE)] = true; // ground or wall
                }
            }
        }
    }

    ~Map() {}
    
    MapSnapshot get_status() { return MapSnapshot(style, size_x, size_y, components, bit_map); }
};

#endif // SERVER_MAP_H
