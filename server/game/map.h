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

class MapConfig
{
public:
    uint16_t style;
    uint16_t size_x;
    uint16_t size_y;
    std::vector<MapComponent> components;
    std::vector<Position> boxes;
    std::map<Position, Spawn> spawns;
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
            spawns.emplace(Position(x, y), type);
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

        for (const auto &box : boxes)
        {
            change_pixels(true, box.x, box.y, TILE_SIZE, TILE_SIZE);
        }
    }
};

class Map
{
private:
    MapConfig cfg;
    uint16_t gun_id;
    std::map<uint8_t, std::shared_ptr<Gun>> guns;
    std::map<Position, Box> boxes;

public:
    Map(const std::string &map_file) : cfg(map_file),
                                       gun_id(0)
    {
        // Eliminar una vez que se tengan los spawns de las armas
        guns.emplace(gun_id, std::make_shared<AK>(290, 320));
        gun_id++;

        for (const auto &position : cfg.boxes)
        {
            boxes.emplace(position, Box::BOX_4_HP);
        }
    }

    std::vector<GunNoEquippedSnapshot> get_guns_snapshots()
    {
        std::vector<GunNoEquippedSnapshot> guns_snapshots;
        for (auto &[id, gun] : guns)
        {
            if (gun.get()->has_been_equipped())
                continue;
            guns_snapshots.push_back(gun.get()->get_status());
        }
        return guns_snapshots;
    }

    MapSnapshot get_status() const
    {
        std::vector<BoxSnapshot> box_snapshots;
        for (auto &[position, box] : boxes)
        {
            box_snapshots.push_back(BoxSnapshot(position, box));
        }

        std::vector<Position> gun_spawns;
        for (auto &[position, spawn] : cfg.spawns)
        {
            if (spawn == Spawn::GUN_SPAWN)
            {
                gun_spawns.push_back(position);
            }
        }
        return MapSnapshot(cfg.style, cfg.size_x, cfg.size_y, cfg.components, box_snapshots, gun_spawns);
    }

    bool validate_coordinate(Position &p) const
    {
        return (p.x < cfg.size_x) && (p.y < cfg.size_y) && !has_something_in(p);
    }

    bool has_something_in(Position &p) const
    {
        return cfg.bit_map[p.x + (p.y * cfg.size_x)];
    }

    std::map<uint8_t, std::shared_ptr<Gun>> &get_guns()
    {
        return guns;
    }

    void remove_gun(uint16_t id)
    {
        guns.erase(id);
    }

    ~Map() {}
};

#endif // SERVER_MAP_H
