#include "explosionsound.h"
#include "../../../common/config.h"

ExplosionSound::ExplosionSound(SDL2pp::Mixer &mixer) : SoundManager(mixer, Config::getInstance()["effect"]["type"]["explosion"].as<int>(), TextureFigure::ExplosionFigure)
{
}

ExplosionSound::~ExplosionSound()
{
}