#include "duck.h"

#define POS_INIT_X_DUCK 1
#define POS_INIT_Y_DUCK 8

#define SRC_GUN_WIDTH 300
#define SRC_GUN_HEIGHT 300
#define POS_INIT_X_GUN 0
#define POS_INIT_Y_GUN 0

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

void Duck::set_xywh(const DuckSnapshot &duck, const int &frame_ticks, int &x, int &y, int &w, int &h)
{
    if (!duck.status.is_alive)
    {
        x = 37;
        y = 90;
        w = 22;
        h = 13;
    }
    else if (duck.status.falling)
    {
        x = 139;
        y = 43;
        h = 24;
    }
    else if (duck.status.start_jumping)
    {
        x = 43;
        y = 46;
        w = 12;
        h = 24;
    }
    else if (duck.status.bent_down)
    {
        x = 5;
        y = 90;
        w = 22;
        h = 13;
    }
    else if (duck.status.mooving)
    {
        int run_phase = (frame_ticks / 4) % 5;
        if (run_phase == 0)
        {
            x = 42;
            y = 14;
            w = 15;
            h = 24;
        }
        else if (run_phase == 1)
        {
            x = 74;
            y = 15;
            w = 14;
            h = 24;
        }
        else if (run_phase == 2)
        {
            x = 107;
            y = 16;
            w = 13;
            h = 23;
        }
        else if (run_phase == 3)
        {
            x = 138;
            y = 14;
            w = 15;
            h = 24;
        }
        else
        {
            x = 171;
            y = 15;
            w = 13;
            h = 24;
        }
    }
}
void Duck::render_helmet_chestplate(DuckSnapshot &duck, CameraSnapshot &camera,
                                    float &scale_x, float &scale_y)
{
    if (duck.status.has_chestplate)
    {
        SDL2pp::Texture &chestplate_texture = get_texture(TextureFigure::Chestplate);
        SDL_Rect src_rect = {0, 0, 78, 60};
        SDL_Rect dst_rect = {
            static_cast<int>((duck.position.x - camera.x) * scale_x),
            static_cast<int>((duck.position.y - camera.y + 8) * scale_y),
            static_cast<int>(CHESTPLATE_WIDTH * scale_x),
            static_cast<int>(CHESTPLATE_HEIGHT * scale_y)};
        SDL_RendererFlip flip = duck.status.looking_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(renderer.Get(), chestplate_texture.Get(), &src_rect, &dst_rect, 0.0, nullptr, flip);
    }
    if (duck.status.has_helmet)
    {
        SDL2pp::Texture &helmet = get_texture(TextureFigure::Helmet);
        SDL_Rect src_rect = {0, 0, 76, 89};
        SDL_Rect dst_rect = {
            static_cast<int>((duck.position.x - camera.x) * scale_x),
            static_cast<int>((duck.position.y - camera.y - 4) * scale_y),
            static_cast<int>(HELMET_WIDTH * scale_x),
            static_cast<int>(HELMET_HEIGHT * scale_y)};

        SDL_RendererFlip flip = duck.status.looking_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(renderer.Get(), helmet.Get(), &src_rect, &dst_rect, 0.0, nullptr, flip);
    }
}

void Duck::render_duck(DuckSnapshot &duck, int frame_ticks, CameraSnapshot &camera,
                       float &scale_x, float &scale_y)
{
    if (((duck.position.x + TILE_SIZE) >= camera.x) && ((duck.position.x - TILE_SIZE) < (camera.x + camera.width)) && ((duck.position.y + TILE_SIZE) >= camera.y) && ((duck.position.y - TILE_SIZE) < (camera.y + camera.height)))
    {
        SDL2pp::Texture &duck_texture = get_texture(TextureFigure::DUCK);
        duck_texture.SetColorMod(duck.color.get_red(), duck.color.get_green(), duck.color.get_blue());
        int x = 8, y = 16;
        int w = 16, h = 23;
        if (!duck.status.banana_move)
            set_xywh(duck, frame_ticks, x, y, w, h);
        SDL_Rect src_rect = {x, y, w, h};
        SDL_Rect dst_rect = {
            static_cast<int>((duck.position.x - camera.x) * scale_x),
            static_cast<int>((duck.position.y - camera.y + (duck.status.is_alive ? 0 : 13)) * scale_y),
            static_cast<int>(w * scale_x),
            static_cast<int>(h * scale_y)};

        SDL_RendererFlip flip = duck.status.looking_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(renderer.Get(), duck_texture.Get(), &src_rect, &dst_rect, 0.0, nullptr, flip);
        render_helmet_chestplate(duck, camera, scale_x, scale_y);
    }
}

void Duck::render_weapon(DuckSnapshot &duck, CameraSnapshot &camera,
                         float &scale_x, float &scale_y)
{
    if (((duck.position_gun.x + TILE_SIZE) >= camera.x) && ((duck.position_gun.x - TILE_SIZE) < (camera.x + camera.width)) && ((duck.position_gun.y + TILE_SIZE) >= camera.y) && ((duck.position_gun.y - TILE_SIZE) < (camera.y + camera.height)))
    {
        Size size = size_factory.get_size(duck.texture_gun);
        SDL2pp::Texture &texture = get_texture(duck.texture_gun);
        int src_x = POS_INIT_X_GUN, src_y = POS_INIT_Y_GUN;
        SDL_RendererFlip flip = duck.status.looking_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
        SDL_Rect src_rect = {src_x, src_y, SRC_GUN_WIDTH, SRC_GUN_HEIGHT};
        SDL_Rect dst_rect = {
            static_cast<int>((duck.position_gun.x - camera.x) * scale_x),
            static_cast<int>((duck.position_gun.y - camera.y) * scale_y),
            static_cast<int>(size.width * scale_x),
            static_cast<int>(size.height * scale_y)};

        SDL_RenderCopyEx(renderer.Get(), texture.Get(), &src_rect, &dst_rect, duck.angle_gun, nullptr, flip);
    }
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Duck::Duck(SDL2pp::Renderer &renderer) : Renderer(renderer) {}

void Duck::render(DuckSnapshot &duck, int frame_ticks, CameraSnapshot &camera,
                  float &scale_x, float &scale_y)
{   
    render_duck(duck, frame_ticks, camera, scale_x, scale_y);
    if (duck.type_gun != GunType::None && duck.status.is_alive)
        render_weapon(duck, camera, scale_x, scale_y);
}

Duck::~Duck() {}