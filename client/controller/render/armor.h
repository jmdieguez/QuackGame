#ifndef ARMOR_CLIENT_H
#define ARMOR_CLIENT_H

#include "../../../common/snapshots.h"
#include "renderer.h"

#define CHESTPLATE_WIDTH 16
#define CHESTPLATE_HEIGHT 12
#define HELMET_WIDTH 16
#define HELMET_HEIGHT 16

class Armor : protected Renderer
{
private:
public:
    explicit Armor(SDL2pp::Renderer &renderer) : Renderer(renderer) {}

    void render(ArmorSnapshot &armor, CameraSnapshot &camera, float &scale_x, float &scale_y)
    {   
        if (armor.type == ArmorType::Chestplate)
        {   
            SDL2pp::Texture &chestplate_texture = get_texture(TextureFigure::Chestplate);
            SDL_Rect src_rect = {0, 0, 78, 60};
            SDL_Rect dst_rect = {
                static_cast<int>((armor.position.x - camera.x) * scale_x),
                static_cast<int>((armor.position.y - camera.y) * scale_y),
                static_cast<int>((CHESTPLATE_WIDTH + 4) * scale_x),
                static_cast<int>((CHESTPLATE_HEIGHT + 4) * scale_y)
            };
            SDL_RenderCopyEx(renderer.Get(), chestplate_texture.Get(), &src_rect, &dst_rect, 0.0, nullptr, SDL_FLIP_NONE);
        }

        else if (armor.type == ArmorType::Helmet)
        {
            SDL2pp::Texture &helmet = get_texture(TextureFigure::Helmet);
            SDL_Rect src_rect = {0, 0, 76, 89};
            SDL_Rect dst_rect = {
                static_cast<int>((armor.position.x - camera.x) * scale_x),
                static_cast<int>((armor.position.y - camera.y) * scale_y),
                static_cast<int>(HELMET_WIDTH * scale_x),
                static_cast<int>(HELMET_HEIGHT * scale_y)
            };
            SDL_RenderCopyEx(renderer.Get(), helmet.Get(), &src_rect, &dst_rect, 0.0, nullptr, SDL_FLIP_NONE);
        }
    }
};

#endif // ARMOR_CLIENT_H
