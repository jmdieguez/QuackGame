#include "sound.h"

#include <memory>
#include "../path.h"
#include "../../common/texturefigure.h"

class SoundFactory
{
private:
    std::string get_path(const TextureFigure &texture);

public:
    SoundFactory();
    std::shared_ptr<Sound> create_texture(const TextureFigure &texture);
    ~SoundFactory();
};