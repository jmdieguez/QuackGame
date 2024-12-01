#ifndef CLIENT_LOADING_SCREEN_H
#define CLIENT_LOADING_SCREEN_H

#include "../ui/defs.h"

#include <vector>
#include "../../common/userlobbyinfo.h"
#include <SDL2pp/SDL2pp.hh>

class LoadingScreen
{
private:
    SDL2pp::Renderer &renderer;
    SDL2pp::Texture icon;
    SDL_Rect tint_rect;
    SDL_Rect src;
    SDL_Rect dst;

public:
    LoadingScreen(SDL2pp::Renderer &r) : renderer(r), icon(renderer, ICON),
                                         tint_rect({0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT}),
                                         src({0, 0, icon.GetWidth(), icon.GetHeight()}),
                                         dst({(DEFAULT_WINDOW_WIDTH - ICON_SIZE) / 2,
                                              (DEFAULT_WINDOW_HEIGHT - ICON_SIZE - 150) / 2,
                                              ICON_SIZE,
                                              ICON_SIZE})
    {
    }

    void set_text_loading(SDL2pp::Font &font)
    {
        SDL2pp::Texture text(renderer, font.RenderText_Blended("THE GAME IS ABOUT TO START...", WHITE));
        SDL_Rect text_src = {0, 0, text.GetWidth(), text.GetHeight()};
        SDL_Rect text_dst = {
            (DEFAULT_WINDOW_WIDTH - text.GetWidth() / 2) / 2,
            dst.y + ICON_SIZE + 32,
            text.GetWidth() / 2,
            text.GetHeight() / 2};
        renderer.Copy(text, text_src, text_dst);
    }

    void set_text_color(SDL2pp::Font &font, std::vector<UserLobbyInfo> &users)
    {
        int base_y = dst.y + ICON_SIZE + 32 + 32;
        int text_spacing_x = 150;

        for (int index = 0; index < (int)users.size(); index++)
        {
            std::string player("Player ");
            std::string player_num = player + std::to_string(index + 1) + ": " + users[index].get_color();
            SDL2pp::Texture text(renderer, font.RenderText_Blended(player_num, WHITE));
            SDL_Rect text_src = {0, 0, text.GetWidth(), text.GetHeight()};

            int text_width = text.GetWidth() / 2;
            int text_height = text.GetHeight() / 2;

            int x_position = (DEFAULT_WINDOW_WIDTH - text_width) / 2;
            if (users.size() == 2)
                x_position += (index == 0) ? -text_spacing_x : text_spacing_x;
            SDL_Rect text_dst = {
                x_position,
                base_y,
                text_width,
                text_height};

            renderer.Copy(text, text_src, text_dst);
        }
    }

    void set_texts(SDL2pp::Font &font, std::vector<UserLobbyInfo> &users)
    {
        set_text_loading(font);
        set_text_color(font, users);
    }

    void render(SDL2pp::Font &font, std::vector<UserLobbyInfo> &users)
    {
        renderer.SetDrawBlendMode(SDL_BLENDMODE_BLEND);
        renderer.SetDrawColor(0, 0, 0, 128);
        renderer.FillRect(tint_rect);
        renderer.SetDrawColor(255, 255, 255, 255);
        renderer.SetDrawBlendMode(SDL_BLENDMODE_NONE);
        set_texts(font, users);
        renderer.Copy(icon, src, dst);
    }
};

#endif // CLIENT_LOADING_SCREEN_H
