#ifndef DUCK_CLIENT_H
#define DUCK_CLIENT_H

#include <SDL2pp/SDL2pp.hh>
#include "../../../common/snapshots.h"
#include "renderer.h"

class Duck : protected Renderer
{
private:
    void set_xy(DuckSnapshot &duck, int frame_ticks, int &src_x, int &src_y);
    void render_helmet_chestplate(DuckSnapshot &duck);
    void render_weapon(DuckSnapshot &duck);
    void render_duck(DuckSnapshot &duck, int frame_ticks);

public:
    explicit Duck(SDL2pp::Renderer &renderer);
    void render(DuckSnapshot &duck, int frame_ticks);
    ~Duck();
};

#endif // DUCK_CLIENT_H