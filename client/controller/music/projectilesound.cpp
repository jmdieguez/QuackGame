#include "projectilesound.h"
#include "../../../common/config.h"

ProjectileGunSound::ProjectileGunSound(SDL2pp::Mixer &mixer) : SoundManager(mixer, Config::getInstance()["effect"]["type"]["projectile_gun"].as<int>(), TextureFigure::CowboyBullet)
{
}

ProjectileGunSound::~ProjectileGunSound()
{
}
