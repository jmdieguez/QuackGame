#ifndef DUCK_CLIENT_H
#define DUCK_CLIENT_H

#include "../../../common/snapshots.h"
#include "textureloader.h"
#include <SDL2pp/SDL2pp.hh>

class Duck : protected TextureLoader
{
private:
    SDL2pp::Renderer &renderer;
    void set_xy(DuckSnapshot &duck, int frame_ticks, int &src_x, int &src_y);
    void render_helmet_chestplate(DuckSnapshot &duck);
    void render_weapon(DuckSnapshot &duck);
    void render_duck(DuckSnapshot &duck, int frame_ticks);

public:
    Duck(SDL2pp::Renderer &renderer);
    void render(DuckSnapshot &duck, int frame_ticks);
    ~Duck();
};

#endif // DUCK_CLIENT_H