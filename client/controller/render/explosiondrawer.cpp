#include "explosiondrawer.h"

#define POS_INIT_X_EXPLOSION 0 // 250
#define POS_INIT_Y_EXPLOSION 0 // 100
#define SRC_PROJECTILE_WIDTH 200
#define SRC_PROJECTILE_HEIGHT 250

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

void ExplosionDrawer::set_xy(int frame_ticks, int &src_x)
{
    int offset = (frame_ticks / 3) % 7;
    int phase = 250 * offset;
    src_x = phase;
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

ExplosionDrawer::ExplosionDrawer(SDL2pp::Renderer &renderer) : Renderer(renderer)
{
}

void ExplosionDrawer::render(ExplosionSnapshot &explosion, int frame_ticks, 
                                 CameraSnapshot &camera, 
                                 float &scale_x, float &scale_y)
{   
    if (((explosion.position.x + TILE_SIZE) >= camera.x)
    && ((explosion.position.x + TILE_SIZE) < (camera.x + camera.width))
    && ((explosion.position.y + TILE_SIZE) >= camera.y)
    && ((explosion.position.y + TILE_SIZE) < (camera.y + camera.height)))
    {  
        SDL2pp::Texture &texture = get_texture(explosion.texture);
        int src_x = POS_INIT_X_EXPLOSION, src_y = POS_INIT_Y_EXPLOSION;
        set_xy(frame_ticks, src_x);
        SDL_Rect src_rect = {src_x, src_y, SRC_PROJECTILE_WIDTH, SRC_PROJECTILE_HEIGHT};
        SDL_Rect dst_rect = {
            static_cast<int>((explosion.position.x - camera.x) * scale_x), 
            static_cast<int>((explosion.position.y - camera.y) * scale_y), 
            static_cast<int>(explosion.size.width * scale_x), 
            static_cast<int>(explosion.size.height * scale_y)
        };

        SDL_RenderCopyEx(renderer.Get(), texture.Get(), &src_rect, &dst_rect, 90.0, nullptr, SDL_FLIP_NONE);
    }
}

ExplosionDrawer::~ExplosionDrawer()
{
}
