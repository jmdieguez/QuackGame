#include "explosionsound.h"

#define VOLUME 10

ExplosionSound::ExplosionSound(SDL2pp::Mixer &mixer) : SoundManager(mixer, VOLUME, TextureFigure::ExplosionFigure)
{
}

ExplosionSound::~ExplosionSound()
{
}