#include "boxitem.h"

BoxItem::BoxItem(SDL2pp::Renderer &renderer) : Renderer(renderer)
{
}

void BoxItem::render(BoxSnapshot &box)
{
    if (box.status == Box::NONE)
        return;
    SDL2pp::Texture &texture = get_texture(TextureFigure::Box_T);
    int x = static_cast<int>(box.status) * texture.GetHeight();
    SDL_Rect src_rect = {x, 0, texture.GetHeight(), texture.GetHeight()};
    SDL_Rect dst_rect = {box.pos.x * TILE_SIZE, box.pos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    renderer.Copy(texture, src_rect, dst_rect);
}

BoxItem::~BoxItem()
{
}
