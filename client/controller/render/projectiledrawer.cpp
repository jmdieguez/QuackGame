#include "projectiledrawer.h"

#define POS_INIT_X_PROJECTILE 0
#define POS_INIT_Y_PROJECTILE 0
#define SRC_PROJECTILE_WIDTH 60
#define SRC_PROJECTILE_HEIGHT 60

#define HORIZONTAL_Y 11
#define HORIZONTAL_RIGHT 10
#define HORIZONTAL_LEFT -5

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

ProjectileDrawer::ProjectileDrawer(SDL2pp::Renderer &renderer) : Renderer(renderer)
{
}

void ProjectileDrawer::render(ProjectileSnapshot &projectile)
{

    if (projectile.texture == TextureFigure::None)
        return;
    Size size = size_factory.get_size(projectile.texture);
    SDL2pp::Texture &texture = get_texture(projectile.texture);
    int src_x = POS_INIT_X_PROJECTILE, src_y = POS_INIT_Y_PROJECTILE;
    bool looking_right = projectile.type_direction == ProjectileDirection::Right;
    SDL_RendererFlip flip = looking_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    SDL_Rect src_rect = {src_x, src_y, SRC_PROJECTILE_WIDTH, SRC_PROJECTILE_HEIGHT};
    SDL_Rect dst_rect = {projectile.pos_x, projectile.pos_y, size.width, size.height};
    SDL_RenderCopyEx(renderer.Get(), texture.Get(), &src_rect, &dst_rect, 0.0, nullptr, flip);
}

ProjectileDrawer::~ProjectileDrawer()
{
}