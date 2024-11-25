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

void Item::render(GunNoEquippedSnapshot &gun)
{
    SDL2pp::Texture &texture = get_texture(gun.texture);
    int src_x = POS_INIT_X_GUN, src_y = POS_INIT_Y_GUN;
    SDL_Rect src_rect = {src_x, src_y, SRC_GUN_WIDTH, SRC_GUN_HEIGHT};
    SDL_Rect dst_rect = {gun.position.x, gun.position.y, gun.size.width, gun.size.height};
    SDL_RenderCopyEx(renderer.Get(), texture.Get(), &src_rect, &dst_rect, 0.0, nullptr, SDL_FLIP_NONE);
}

Item::~Item()
{
}
