#include "duck.h"

#include "../../model/resource/texturestorage.h"
#include "../../../common/texturefigure.h"

#define DUCK_HEIGHT 32
#define DUCK_WIDTH 32
#define SRC_DUCK_WIDTH 32
#define SRC_DUCK_HEIGHT 32
#define POS_INIT_X_DUCK 1
#define POS_INIT_Y_DUCK 8

#define SRC_GUN_WIDTH 300
#define SRC_GUN_HEIGHT 300
#define POS_INIT_X_GUN 0
#define POS_INIT_Y_GUN 0

#define CHESTPLATE_WIDTH 20
#define CHESTPLATE_HEIGHT 15

#define HELMET_WIDTH 20
#define HELMET_HEIGHT 20

/***************************************************************************
                              PRIVATE METHODS
****************************************************************************/

void Duck::set_xy(DuckSnapshot &duck, int frame_ticks, int &src_x, int &src_y)
{

    if (!duck.status.is_alive)
        src_y += DUCK_HEIGHT * 2;
    else if (duck.status.falling)
    {
        src_x += DUCK_WIDTH * 3;
        src_y += DUCK_HEIGHT;
    }
    else if (duck.status.start_jumping)
    {
        src_x += DUCK_WIDTH;
        src_y += DUCK_HEIGHT;
    }
    else if (duck.status.bent_down)
        src_y += DUCK_HEIGHT * 2;
    else if (duck.status.mooving)
    {
        int run_phase = (frame_ticks / 4) % 5 + 1;
        src_x = SRC_DUCK_WIDTH * run_phase;
    }
}

void Duck::render_helmet_chestplate(DuckSnapshot &duck)
{
    int src_x = POS_INIT_X_DUCK, src_y = POS_INIT_Y_DUCK;
    if (duck.status.has_chestplate)
    {
        SDL2pp::Texture &chestplate_texture = get_texture(TextureFigure::Chestplate);
        SDL_Rect src_rect = {src_x, src_y, SRC_DUCK_WIDTH, SRC_DUCK_HEIGHT};
        SDL_Rect dst_rect = {duck.position.x + (duck.status.looking_right ? 3 : 8), duck.position.y + 15, CHESTPLATE_WIDTH, CHESTPLATE_HEIGHT};
        SDL_RendererFlip flip = duck.status.looking_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(renderer.Get(), chestplate_texture.Get(), &src_rect, &dst_rect, 0.0, nullptr, flip);
    }
    if (duck.status.has_helmet)
    {
        SDL2pp::Texture &helmet = get_texture(TextureFigure::Helmet);
        SDL_Rect src_rect = {src_x, src_y, SRC_DUCK_WIDTH, SRC_DUCK_HEIGHT};
        SDL_Rect dst_rect = {duck.position.x + (duck.status.looking_right ? 3 : 8), duck.position.y - 2, HELMET_WIDTH, HELMET_HEIGHT};
        SDL_RendererFlip flip = duck.status.looking_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(renderer.Get(), helmet.Get(), &src_rect, &dst_rect, 0.0, nullptr, flip);
    }
}

void Duck::render_duck(DuckSnapshot &duck, int frame_ticks)
{
    SDL2pp::Texture &duck_texture = get_texture(TextureFigure::DUCK);
    int src_x = POS_INIT_X_DUCK, src_y = POS_INIT_Y_DUCK;
    set_xy(duck, frame_ticks, src_x, src_y);
    SDL_Rect src_rect = {src_x, src_y, SRC_DUCK_WIDTH, SRC_DUCK_HEIGHT};
    SDL_Rect dst_rect = {duck.position.x, duck.position.y, duck.size_duck.width, duck.size_duck.height};
    SDL_RendererFlip flip = duck.status.looking_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(renderer.Get(), duck_texture.Get(), &src_rect, &dst_rect, 0.0, nullptr, flip);
}

void Duck::render_weapon(DuckSnapshot &duck)
{
    SDL2pp::Texture &texture = get_texture(duck.texture_gun);
    int src_x = POS_INIT_X_GUN, src_y = POS_INIT_Y_GUN;
    SDL_RendererFlip flip = duck.status.looking_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    SDL_Rect src_rect = {src_x, src_y, SRC_GUN_WIDTH, SRC_GUN_HEIGHT};
    SDL_Rect dst_rect = {duck.position_gun.x, duck.position_gun.y, duck.size_gun.width, duck.size_gun.height};
    SDL_RenderCopyEx(renderer.Get(), texture.Get(), &src_rect, &dst_rect, duck.angle_gun, nullptr, flip);
}

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Duck::Duck(SDL2pp::Renderer &renderer) : Renderer(renderer) {}
void Duck::render(DuckSnapshot &duck, int frame_ticks)
{
    render_duck(duck, frame_ticks);
    render_helmet_chestplate(duck);
    if (duck.type_gun != GunType::None)
        render_weapon(duck);
}
Duck::~Duck() {}