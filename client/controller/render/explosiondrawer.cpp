#include "explosiondrawer.h"

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

void ExplosionDrawer::set_xywh(const int &frame_ticks, int &x, int &y, int &w, int &h)
{
    int phase = (frame_ticks / 4) % 8;
    if (phase == 0)
    {
        x = 90;
        y = 80;
        w = 80;
        h = 80;
    }
    else if (phase == 1)
    {
        x = 331;
        y = 82;
        w = 80;
        h = 80;
    }
    else if (phase == 2)
    {
        x = 573;
        y = 85;
        w = 80;
        h = 80;
    }
    else if (phase == 3)
    {
        x = 812;
        y = 85;
        w = 80;
        h = 80;
    }

    else if (phase == 4)
    {
        x = 1040;
        y = 68;
        w = 112;
        h = 112;
    }

    else if (phase == 5)
    {
        x = 1277;
        y = 67;
        w = 112;
        h = 112;
    }
    else if (phase == 6)
    {
        x = 1509;
        y = 50;
        w = 130;
        h = 134;
    }
    else
    {
        x = 1746;
        y = 47;
        w = 140;
        h = 140;
    }
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
        int x, y, w, h;
        set_xywh(frame_ticks, x, y, w, h);
        SDL_Rect src_rect = {x, y, w, h};
        SDL_Rect dst_rect = {
            static_cast<int>((explosion.position.x - camera.x) * scale_x), 
            static_cast<int>((explosion.position.y - camera.y) * scale_y), 
            static_cast<int>(40 * scale_x), 
            static_cast<int>(40 * scale_y)
        };

        SDL_RenderCopyEx(renderer.Get(), texture.Get(), &src_rect, &dst_rect, 90.0, nullptr, SDL_FLIP_NONE);
    }
}

ExplosionDrawer::~ExplosionDrawer()
{
}
