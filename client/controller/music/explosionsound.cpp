#include "explosionsound.h"

#define VOLUME 3

ExplosionSound::ExplosionSound(SDL2pp::Mixer &mixer) : SoundManager(mixer, VOLUME, TextureFigure::ExplosionFigure)
{
}

ExplosionSound::~ExplosionSound()
{
}