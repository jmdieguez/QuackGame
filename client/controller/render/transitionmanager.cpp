
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

void TransitionManager::fadeTransition(bool fadeOut) {

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, "Next level!", white);

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer.Get(), textSurface);
    if (!textTexture) {
        SDL_FreeSurface(textSurface);
        throw std::runtime_error("Failed to create texture from text: " + std::string(SDL_GetError()));
    }

    int textWidth = textSurface->w;
    int textHeight = textSurface->h;
    SDL_FreeSurface(textSurface);

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
        SDL_DestroyTexture(textTexture);
    }

    Mix_PlayChannel(-1, sound, 0);

    Uint32 startTicks = SDL_GetTicks();
    Uint32 endTicks = startTicks + 150 * 16;

    while (SDL_GetTicks() < endTicks) {
        Uint32 elapsed = SDL_GetTicks() - startTicks;
        alpha = fadeOut ? 255 - (elapsed * 255 / (150 * 16)) : (elapsed * 255 / (150 * 16));
        if (alpha < 0) alpha = 0;
        if (alpha > 255) alpha = 255;

        SDL_SetRenderDrawColor(renderer.Get(), 0, 0, 0, alpha);
        SDL_RenderClear(renderer.Get());
        SDL_RenderCopy(renderer.Get(), textTexture, nullptr, &textRect);
        SDL_RenderPresent(renderer.Get());
    }

    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    Mix_FreeChunk(sound);
}


void TransitionManager::drawTransitionOverlay() {
    SDL_SetRenderDrawColor(renderer.Get(), 0, 0, 0, alpha);
    SDL_RenderFillRect(renderer.Get(), nullptr);
    SDL_RenderPresent(renderer.Get());
}