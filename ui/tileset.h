#ifndef UI_TILESET_H
#define UI_TILESET_H

#include <memory>
#include <map>
#include <SDL2pp/SDL2pp.hh>

#include "../common/snapshots.h"

class Tileset {
    
public:
    std::map<Component, std::shared_ptr<SDL2pp::Texture>> textures;
    std::map<Component, SDL_Rect> areas;
    
    Tileset(uint8_t &style, SDL2pp::Renderer &renderer, std::shared_ptr<SDL2pp::Texture> all_tilesets) {
        areas = {
            { Component::SINGLE_GROUND, {16 + (style * 128), 0, 16, 16} },
            { Component::BIG_WALL_GROUND, {0 + (style * 128), 16, 48, 16} },
            { Component::BIG_WALL, {0 + (style * 128), 32, 48, 16} },
            { Component::BIG_WALL_BASE, {0 + (style * 128), 48, 48, 16} },
            { Component::SLIM_WALL, {48 + (style * 128), 16, 16, 48} },
            { Component::LONG_GROUND, {64 + (style * 128), 16, 48, 16} }
        };

        for (const auto& [key, area] : areas) {
            std::shared_ptr<SDL2pp::Texture> texture = std::make_shared<SDL2pp::Texture>
                (renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, area.w, area.h);
            renderer.SetTarget(*texture);
            renderer.Clear();
            renderer.Copy(*all_tilesets, area, SDL_Rect{0, 0, area.w, area.h});
            renderer.SetTarget();
            textures.emplace(key, texture);
        }
    }

    ~Tileset() {}
};

#endif // UI_TILESET_H