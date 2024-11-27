#include "boxitem.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

BoxItem::BoxItem(SDL2pp::Renderer &renderer) : Renderer(renderer)
{
}

void BoxItem::render(BoxSnapshot &box, 
                     CameraSnapshot &camera, 
                     float &scale_x, float &scale_y)
{
    if (box.status == Box::NONE)
        return;

    int x = box.pos.x * TILE_SIZE;
    int y = box.pos.y * TILE_SIZE;

    if (((x + TILE_SIZE) >= camera.x)
    && ((x - TILE_SIZE) < (camera.x + camera.width))
    && ((y + TILE_SIZE) >= camera.y)
    && ((y - TILE_SIZE) < (camera.y + camera.height)))
    {  
        SDL2pp::Texture &texture = get_texture(TextureFigure::Box_T);
        int src_x = static_cast<int>(box.status) * texture.GetHeight();
        SDL_Rect src_rect = {src_x, 0, texture.GetHeight(), texture.GetHeight()};
        SDL_Rect dst_rect = {
            static_cast<int>((x - camera.x) * scale_x),
            static_cast<int>((y - camera.y) * scale_y),
            static_cast<int>(TILE_SIZE * scale_x), 
            static_cast<int>(TILE_SIZE * scale_y)
        };
        renderer.Copy(texture, src_rect, dst_rect);
    }
}

BoxItem::~BoxItem()
{
}
