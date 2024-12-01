
#include "transitionmanager.h"
#include "../../model/resource/path.h"
#include <SDL2pp/SDL2pp.hh>
#include <SDL_ttf.h>
#include <SDL_mixer.h>



TransitionManager::TransitionManager(SDL2pp::Renderer &renderer, SDL2pp::Font &font)
    : renderer(renderer), font(font), transitionTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 800, 600) {
    alpha = 0;
    transitionTexture.SetBlendMode(SDL_BLENDMODE_BLEND);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void TransitionManager::fadeTransition() {
    SDL2pp::Surface textSurface = font.RenderText_Blended("Next level!", SDL2pp::Color(255, 255, 255));
    SDL2pp::Texture textTexture(renderer, textSurface);

    int textWidth = textSurface.GetWidth();
    int textHeight = textSurface.GetHeight();

    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer.Get(), &windowWidth, &windowHeight);

    SDL_Rect textRect = {
        (windowWidth - textWidth) / 2,
        (windowHeight - textHeight) / 2,
        textWidth,
        textHeight
    };

    Mix_Chunk* sound = Mix_LoadWAV(NEXT_LEVEL);
    if (!sound) {
        throw std::runtime_error("Failed to load sound: " + std::string(Mix_GetError()));
    }
    Mix_PlayChannel(-1, sound, 0);

    Uint32 startTicks = SDL_GetTicks();
    Uint32 fadeDuration = 50 * 16;

    Uint32 endTicks = startTicks + fadeDuration;

    while (SDL_GetTicks() < endTicks) {
        Uint32 elapsed = SDL_GetTicks() - startTicks;
        alpha = elapsed * 255 / fadeDuration;
        if (alpha < 0) alpha = 0;
        if (alpha > 255) alpha = 255;

        SDL_SetRenderDrawColor(renderer.Get(), 0, 0, 0, alpha);
        SDL_RenderClear(renderer.Get());
        SDL_RenderCopy(renderer.Get(), textTexture.Get(), nullptr, &textRect);
        SDL_RenderPresent(renderer.Get());
    }

    startTicks = SDL_GetTicks();
    endTicks = startTicks + fadeDuration;

    while (SDL_GetTicks() < endTicks) {
        Uint32 elapsed = SDL_GetTicks() - startTicks;
        alpha = 255 - (elapsed * 255 / fadeDuration);
        if (alpha < 0) alpha = 0;
        if (alpha > 255) alpha = 255;

        SDL_SetRenderDrawColor(renderer.Get(), 0, 0, 0, alpha);
        SDL_RenderClear(renderer.Get());
        SDL_RenderCopy(renderer.Get(), textTexture.Get(), nullptr, &textRect);
        SDL_RenderPresent(renderer.Get());
    }

    Mix_FreeChunk(sound);
}



void TransitionManager::drawTransitionOverlay() {
    SDL_SetRenderDrawColor(renderer.Get(), 0, 0, 0, alpha);
    SDL_RenderFillRect(renderer.Get(), nullptr);
    SDL_RenderPresent(renderer.Get());
}