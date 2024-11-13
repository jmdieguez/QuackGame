#ifndef SOUND_STORAGE_H
#define SOUND_STORAGE_H

#include <map>
#include <memory>

#include "soundfactory.h"

class SoundStorage
{
private:
    SoundFactory factory;
    std::map<SoundType, std::shared_ptr<Sound>> sounds_created;

public:
    static SoundStorage &get_instance();
    std::shared_ptr<Sound> get_sound(SoundType sound);
    ~SoundStorage();
};

#endif // SOUND_STORAGE_H