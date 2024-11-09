#ifndef COMMON_MAP_H
#define COMMON_MAP_H

#include <vector>
#include <yaml-cpp/yaml.h>
#include <cstdint>
#include <stdexcept>
#include <utility>

#include "defs.h"

#define DIMENSIONS_FILE "./dimensions.yaml"

enum class Spawn : uint16_t {
    GUN_SPAWN = 1,
    DUCK_SPAWN
};

enum class Box : uint16_t {
    NONE = 0,
    BOX_1_HP,
    BOX_2_HP,
    BOX_3_HP,
    BOX_4_HP
};

enum class Component : uint16_t
{
    NONE = 0,
    BIG_WALL,
    BIG_WALL_BASE,
    BIG_WALL_GROUND,
    LONG_GROUND,
    SINGLE_GROUND,
    SLIM_WALL
};

namespace YAML
{
    template <> struct convert<Component>
    {
        static Node encode(const Component &rhs)
        {
            Node node;
            node = static_cast<uint16_t>(rhs);
            return node;
        }

        static bool decode(const Node &node, Component &rhs)
        {
            if (!node.IsScalar())
                return false;
            uint16_t value = node.as<uint16_t>();

            switch (value)
            {
            case 0:
                rhs = Component::NONE;
                break;
            case 1:
                rhs = Component::BIG_WALL;
                break;
            case 2:
                rhs = Component::BIG_WALL_BASE;
                break;
            case 3:
                rhs = Component::BIG_WALL_GROUND;
                break;
            case 4:
                rhs = Component::LONG_GROUND;
                break;
            case 5:
                rhs = Component::SINGLE_GROUND;
                break;
            case 6:
                rhs = Component::SLIM_WALL;
                break;
            default:
                throw std::runtime_error("Error while reading map components");
            }
            return true;
        }
    };

    template <> struct convert<Spawn>
    {
        static Node encode(const Spawn &rhs)
        {
            Node node;
            node = static_cast<uint16_t>(rhs);
            return node;
        }

        static bool decode(const Node &node, Spawn &rhs)
        {
            if (!node.IsScalar())
                return false;
            uint16_t value = node.as<uint16_t>();

            switch (value)
            {
            case 1:
                rhs = Spawn::GUN_SPAWN;
                break;
            case 2:
                rhs = Spawn::DUCK_SPAWN;
                break;
            default:
                throw std::runtime_error("Error while reading map spawns");
            }
            return true;
        }
    };
}

class MapComponent
{
public:
    uint16_t x;
    uint16_t y;
    Component type;
    MapComponent(uint16_t &pos_x, uint16_t &pos_y, Component &c) : x(pos_x), y(pos_y), type(c) {}

    ~MapComponent() {}
};

#endif // COMMON_MAP_H
