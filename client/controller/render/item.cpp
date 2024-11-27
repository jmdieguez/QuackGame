#include "item.h"

#define GUN_HEIGHT 16
#define SRC_GUN_WIDTH 300
#define SRC_GUN_HEIGHT 300
#define POS_INIT_X_GUN 0
#define POS_INIT_Y_GUN 0

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Item::Item(SDL2pp::Renderer &renderer) : Renderer(renderer)
{
}

void Item::render(GunNoEquippedSnapshot &gun, 
                  CameraSnapshot &camera, 
                  float &scale_x, float &scale_y)
{   
    if (((gun.position.x + TILE_SIZE) >= camera.x)
    && ((gun.position.x + TILE_SIZE) < (camera.x + camera.width))
    && ((gun.position.y + TILE_SIZE) >= camera.y)
    && ((gun.position.y + TILE_SIZE) < (camera.y + camera.height)))
    {   
        Size size = size_factory.get_size(gun.texture);
        SDL2pp::Texture &texture = get_texture(gun.texture);
        int src_x = POS_INIT_X_GUN, src_y = POS_INIT_Y_GUN;
        SDL_Rect src_rect = {src_x, src_y, SRC_GUN_WIDTH, SRC_GUN_HEIGHT};
        SDL_Rect dst_rect = {
            static_cast<int>((gun.position.x - camera.x) * scale_x), 
            static_cast<int>((gun.position.y - camera.y) * scale_y), 
            static_cast<int>(size.width * scale_x), 
            static_cast<int>(size.height * scale_y)
        };
        SDL_RenderCopyEx(renderer.Get(), texture.Get(), &src_rect, &dst_rect, 0.0, nullptr, SDL_FLIP_NONE);
    }
}

Item::~Item()
{
}
