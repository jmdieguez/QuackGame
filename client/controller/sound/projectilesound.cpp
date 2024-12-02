#include "projectilesound.h"

ProjectileGunSound::ProjectileGunSound(SDL2pp::Mixer &mixer, unsigned &volume) : SoundManager(mixer, volume, TextureFigure::CowboyBullet)
{
}

ProjectileGunSound::~ProjectileGunSound()
{
}
