#ifndef BOX_ITEM_CLIENT_H
#define BOX_ITEM_CLIENT_H

#include "../../../common/snapshots.h"
#include "renderer.h"

class BoxItem : protected Renderer
{
private:
public:
    explicit BoxItem(SDL2pp::Renderer &renderer);
    void render(BoxSnapshot &box, 
                                 CameraSnapshot &camera, 
                                 float &scale_x, float &scale_y);
    ~BoxItem();
};

#endif // BOX_ITEM_CLIENT_H