#ifndef ITEM_CLIENT_H
#define ITEM_CLIENT_H

#include <SDL2pp/SDL2pp.hh>
#include "../../../common/snapshots.h"
#include "renderer.h"

class Item : protected Renderer
{
private:
public:
    explicit Item(SDL2pp::Renderer &renderer);
    void render(GunNoEquippedSnapshot &gun);
    ~Item();
};

#endif // ITEM_CLIENT_H