#ifndef CLIENT_LOADING_SCREEN_H
#define CLIENT_LOADING_SCREEN_H

#include "../ui/defs.h"

#include <SDL2pp/SDL2pp.hh>

class LoadingScreen {
private:
    SDL2pp::Renderer &renderer;
    SDL2pp::Texture icon;
    SDL_Rect tint_rect;
    SDL_Rect src;
    SDL_Rect dst;
    SDL2pp::Texture text;
    SDL_Rect text_src;
    SDL_Rect text_dst;
public:
    LoadingScreen(SDL2pp::Renderer &r, SDL2pp::Font &font) : renderer(r), icon(renderer, ICON),
                      tint_rect({0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT}),
                      src({0, 0, icon.GetWidth(), icon.GetHeight()}),
                      dst({
                            (DEFAULT_WINDOW_WIDTH - ICON_SIZE) / 2,
                            (DEFAULT_WINDOW_HEIGHT - ICON_SIZE) / 2,
                            ICON_SIZE,
                            ICON_SIZE
                        }),
                      text(renderer, font.RenderText_Blended("THE GAME IS ABOUT TO START...", WHITE)),
                      text_src({0, 0, text.GetWidth(), text.GetHeight()}),
                      text_dst({
                           (DEFAULT_WINDOW_WIDTH - text.GetWidth()) / 2,
                           dst.y + ICON_SIZE + 32,
                           text.GetWidth(),
                           text.GetHeight()
                        })
    {
    }
    
    void render() {
        renderer.SetDrawBlendMode(SDL_BLENDMODE_BLEND);
        renderer.SetDrawColor(0, 0, 0, 128);
        renderer.FillRect(tint_rect);
        renderer.SetDrawColor(255, 255, 255, 255);
        renderer.SetDrawBlendMode(SDL_BLENDMODE_NONE);
        renderer.Copy(icon, src, dst);
        renderer.Copy(text, text_src, text_dst);
    }
};

#endif // CLIENT_LOADING_SCREEN_H
