#include "projectilelasersound.h"

ProjectileLaserSound::ProjectileLaserSound(SDL2pp::Mixer &mixer, unsigned &volume) : SoundManager(mixer, volume, TextureFigure::LaserRifleBullet)
{
}

ProjectileLaserSound::~ProjectileLaserSound()
{
}
