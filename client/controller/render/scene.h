#include <SDL2pp/SDL2pp.hh>
#include "renderer.h"
#include "../../../common/snapshots.h"

class Scene : protected Renderer
{
private:
public:
    explicit Scene(SDL2pp::Renderer &renderer);
    void render();
    ~Scene();
};
