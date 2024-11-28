#include "projectilesound.h"

#define MAX_QUANTITY_SOUNDS 3

ProjectileGunSound::ProjectileGunSound(SDL2pp::Mixer &mixer) : current_quantity_sound(0),
                                                               music_box(mixer)
{
}

bool ProjectileGunSound::listened(uint16_t id)
{
    return ids_projectile.find(id) != ids_projectile.end();
}

void ProjectileGunSound::sound(uint16_t id)
{
    if (listened(id) || current_quantity_sound >= MAX_QUANTITY_SOUNDS)
        return;
    music_box.play_sound(TextureFigure::CowboyBullet);
    ids_projectile.insert(id);
    current_quantity_sound++;
}

void ProjectileGunSound::clear()
{
    current_quantity_sound = 0;
}

ProjectileGunSound::~ProjectileGunSound()
{
}
