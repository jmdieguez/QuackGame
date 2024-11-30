
#include "transitionmanager.h"

TransitionManager::TransitionManager(SDL2pp::Renderer &renderer)
    : renderer(renderer), transitionTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 800, 600)
{
    alpha = 0;
    transitionTexture.SetBlendMode(SDL_BLENDMODE_BLEND);
}

void TransitionManager::fadeTransition(int duration, bool fadeOut) {
    int step = fadeOut ? -255 / duration : 255 / duration;
    for (int i = 0; i < duration; ++i) {
        SDL_SetRenderDrawColor(renderer.Get(), 0, 0, 0, alpha);
        SDL_RenderFillRect(renderer.Get(), nullptr);
        SDL_RenderPresent(renderer.Get());
        SDL_Delay(16);

        alpha += step;
        if (fadeOut && alpha < 0) alpha = 0;
        if (!fadeOut && alpha > 255) alpha = 255;
    }
}

void TransitionManager::drawTransitionOverlay() {
    SDL_SetRenderDrawColor(renderer.Get(), 0, 0, 0, alpha);
    SDL_RenderFillRect(renderer.Get(), nullptr);
    SDL_RenderPresent(renderer.Get());
}