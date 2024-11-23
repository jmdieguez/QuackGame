#include "explosiondrawer.h"

#define POS_INIT_X_EXPLOSION 2
#define POS_INIT_Y_EXPLOSION 1
#define SRC_PROJECTILE_WIDTH 6
#define SRC_PROJECTILE_HEIGHT 16

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

void ExplosionDrawer::set_xy(int frame_ticks, int &src_x)
{
    (void)frame_ticks;
    // int phase = (frame_ticks / 4) % 4 + 1;
    src_x = 4;
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

ExplosionDrawer::ExplosionDrawer(SDL2pp::Renderer &renderer) : Renderer(renderer)
{
}

void ExplosionDrawer::render(ExplosionSnapshot &explosion, int frame_ticks)
{
    SDL2pp::Texture &texture = get_texture(explosion.texture);
    int src_x = POS_INIT_X_EXPLOSION, src_y = POS_INIT_Y_EXPLOSION;
    set_xy(frame_ticks, src_x);
    SDL_Rect src_rect = {src_x, src_y, SRC_PROJECTILE_WIDTH, SRC_PROJECTILE_HEIGHT};
    SDL_Rect dst_rect = {explosion.position.x, explosion.position.y, explosion.size.width, explosion.size.height};
    SDL_RenderCopyEx(renderer.Get(), texture.Get(), &src_rect, &dst_rect, 0.0, nullptr, SDL_FLIP_NONE);
}

ExplosionDrawer::~ExplosionDrawer()
{
}
