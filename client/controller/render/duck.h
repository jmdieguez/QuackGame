#ifndef DUCK_CLIENT_H
#define DUCK_CLIENT_H

#include "armor.h"
#include "renderer.h"
#include "size/gun/gunsizefactory.h"
#include "../../../common/snapshots.h"

class Duck : protected Renderer
{
private:
    GunSizeFactory size_factory;

    void set_xywh(const DuckSnapshot &duck, const int &frame_ticks, int &x, int &y, int &w, int &h);
    void render_helmet_chestplate(DuckSnapshot &duck, CameraSnapshot &camera, 
                                 float &scale_x, float &scale_y);
    void render_weapon(DuckSnapshot &duck, CameraSnapshot &camera, 
                                 float &scale_x, float &scale_y);
    void render_duck(DuckSnapshot &duck, int frame_ticks, CameraSnapshot &camera, 
                                 float &scale_x, float &scale_y);

public:
    explicit Duck(SDL2pp::Renderer &renderer);
    void render(DuckSnapshot &duck, int frame_ticks, CameraSnapshot &camera, 
                float &scale_x, float &scale_y);
    ~Duck();
};

#endif // DUCK_CLIENT_H