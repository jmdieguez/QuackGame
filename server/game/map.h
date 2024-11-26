#ifndef SERVER_MAP_H
#define SERVER_MAP_H

#include "../../common/snapshots.h"
#include "../../common/map.h"
#include "../../common/position.h"
#include "gun/cowboypistol.h"
#include "gun/magnum.h"
#include "gun/duelingpistol.h"
#include "gun/shotgun.h"
#include "gun/sniper.h"
#include "gun/ak.h"
#include "gun/pewpewlaser.h"
#include "gun/grenade.h"
#include "gun/banana.h"

class MapConfig
{
public:
    uint16_t style;
    uint16_t size_x;
    uint16_t size_y;
    std::vector<MapComponent> components;
    std::vector<Position> boxes;
    std::vector<Position> duck_spawns;
    std::vector<Position> gun_spawns;
    std::vector<bool> bit_map; // true: wall/ground. false: empty space
    std::map<Component, std::pair<uint8_t, uint8_t>> dimensions;

    MapConfig(const std::string &filename)
    {
        YAML::Node root = YAML::LoadFile(filename);

        uint16_t n_tiles_x = root["n_tiles_x"].as<uint16_t>();
        uint16_t n_tiles_y = root["n_tiles_y"].as<uint16_t>();
        style = root["tileset"].as<uint16_t>();
        for (const auto &itemNode : root["components"])
        {
            uint16_t x = itemNode["x"].as<uint16_t>();
            uint16_t y = itemNode["y"].as<uint16_t>();
            Component component = itemNode["type"].as<Component>();
            components.push_back(MapComponent(x, y, component));
        }

        for (const auto &itemNode : root["spawns"])
        {
            uint16_t x = itemNode["x"].as<uint16_t>();
            uint16_t y = itemNode["y"].as<uint16_t>();
            Spawn type = itemNode["type"].as<Spawn>();
            if (type == Spawn::GUN_SPAWN)
            {
                gun_spawns.push_back(Position(x, y));
            }
            else if (type == Spawn::DUCK_SPAWN)
            {
                duck_spawns.push_back(Position(x, y));
            }
        }

        for (const auto &itemNode : root["boxes"])
        {
            uint16_t x = itemNode["x"].as<uint16_t>();
            uint16_t y = itemNode["y"].as<uint16_t>();
            boxes.push_back(Position(x, y));
        }

        size_x = n_tiles_x * TILE_SIZE;
        size_y = n_tiles_y * TILE_SIZE;
        bit_map = std::vector(size_x * size_y, false);
        initiate_components_dimensions();
        initiate_components();
    }

    void initiate_components_dimensions()
    {
        YAML::Node root = YAML::LoadFile(DIMENSIONS_FILE);
        for (const auto &dim : root["components"])
        {
            Component type = dim["type"].as<Component>();
            uint16_t dim_x = dim["dim_x"].as<uint16_t>(); // n tiles
            uint16_t dim_y = dim["dim_y"].as<uint16_t>();
            dimensions.emplace(type, std::make_pair(dim_x * TILE_SIZE, dim_y * TILE_SIZE));
        }
    }

    void change_pixels(const bool &ocuppied, const int &x, const int &y, const int &w, const int &h)
    {
        int start_x = x * TILE_SIZE;
        int start_y = y * TILE_SIZE;
        for (int i = 0; i < w; i++)
        {
            int x_pos = start_x + i;
            for (int j = 0; j < h; j++)
            {
                int y_pos = start_y + j;
                bit_map[x_pos + (y_pos * size_x)] = ocuppied;
            }
        }
    }

    void initiate_components()
    {
        for (const MapComponent &component : components)
        {
            std::pair<int, int> component_dimensions = dimensions[component.type];
            change_pixels(true, component.x, component.y, component_dimensions.first, component_dimensions.second);
        }
    }
};

class Map
{
private:
    MapConfig cfg;

public:
    Map(const std::string &map_file) : cfg(map_file)
    {
    }

    bool is_hitbox_valid(const Hitbox &hitbox) const
    {

        Position pos = hitbox.get_position();
        Size size = hitbox.get_size();
        for (uint16_t x = pos.x; x < pos.x + size.width; x++)
        {
            for (uint16_t y = pos.y; y < pos.y + size.height; y++)
            {
                Position p(x, y);
                if (!validate_coordinate(p))
                    return false;
            }
        }

        return true;
    }

    MapSnapshot get_status() const
    {
        return MapSnapshot(cfg.style, cfg.size_x, cfg.size_y, cfg.components, cfg.gun_spawns);
    }

    bool in_range(const Position &p) const
    {
        return (p.x < cfg.size_x) && (p.y < cfg.size_y);
    }

    bool validate_coordinate(const Position &p) const
    {
        return !has_something_in(p);
    }

    bool has_something_in(const Position &p) const
    {
        if (in_range(p))
        {
            return cfg.bit_map[p.x + (p.y * cfg.size_x)];
        }
        return false;
    }

    std::vector<Position> calculate_spawns(const int &n_players) const
    {
        std::vector<Position> spawns;

        for (int n = 0; n < n_players; n++)
        {
            Position p = cfg.duck_spawns[n % cfg.duck_spawns.size()]; // Expressed as (row, file) of tiles
            Position p_as_pixels(p.x * TILE_SIZE, p.y * TILE_SIZE);
            spawns.push_back(p_as_pixels);
        }

        return spawns;
    }

    std::vector<Position> get_boxes_spawns() const
    {
        return cfg.boxes;
    }

    std::vector<Position> get_guns_spawns() const
    {
        return cfg.gun_spawns;
    }

    ~Map() {}
};

#endif // SERVER_MAP_H
