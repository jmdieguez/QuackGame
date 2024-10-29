#ifndef EDITOR_TILESET_H
#define EDITOR_TILESET_H

#include <memory>
#include <map>
#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

class Tileset {
    
public:
    std::map<std::string, std::shared_ptr<Texture>> textures;
    std::map<std::string, SDL_Rect> areas;
    
    Tileset(uint8_t &style, Renderer &renderer, std::shared_ptr<Texture> all_tilesets) {
        areas = {
            {"SINGLE_GROUND", {16 + (style * 128), 0, 16, 16}},
            {"BIG_WALL_GROUND", {0 + (style * 128), 16, 48, 16}},
            {"BIG_WALL", {0 + (style * 128), 32, 48, 16}},
            {"BIG_WALL_BASE", {0 + (style * 128), 48, 48, 16}},
            {"SLIM_WALL", {48 + (style * 128), 16, 16, 48}},
            {"LONG_GROUND", {64 + (style * 128), 16, 48, 16}}
        };

        for (const auto& [key, area] : areas) {
            std::shared_ptr<Texture> texture = std::make_shared<Texture>
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

#endif // TILESET_H