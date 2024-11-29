#include "projectilesound.h"

#define VOLUME 1

ProjectileGunSound::ProjectileGunSound(SDL2pp::Mixer &mixer) : SoundManager(mixer, VOLUME, TextureFigure::CowboyBullet)
{
}

ProjectileGunSound::~ProjectileGunSound()
{
}
