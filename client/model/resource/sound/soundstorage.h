#ifndef SOUND_STORAGE_H
#define SOUND_STORAGE_H

#include <map>
#include <memory>

#include "soundfactory.h"

class SoundStorage
{
private:
    SoundFactory factory;
    std::map<TextureFigure, std::shared_ptr<Sound>> sounds_created;

public:
    static SoundStorage &get_instance();
    std::shared_ptr<Sound> get_sound(const TextureFigure &sound);
    ~SoundStorage();
};

#endif // SOUND_STORAGE_H