#include "sound.h"

#include <memory>
#include "../path.h"
#include "../../common/soundtype.h"

class SoundFactory
{
private:
    std::string get_path(SoundType sound);

public:
    SoundFactory();
    std::shared_ptr<Sound> create_texture(SoundType sound);
    ~SoundFactory();
};