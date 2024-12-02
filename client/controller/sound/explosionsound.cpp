#include "explosionsound.h"

ExplosionSound::ExplosionSound(SDL2pp::Mixer &mixer, unsigned &volume) : SoundManager(mixer, volume, TextureFigure::ExplosionFigure)
{
}

ExplosionSound::~ExplosionSound()
{
}