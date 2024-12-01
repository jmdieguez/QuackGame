#ifndef TABLE_SCREEN_H
#define TABLE_SCREEN_H

#include "../ui/defs.h"

#include <vector>
#include "../../common/snapshots.h"
#include <SDL2pp/SDL2pp.hh>

class TableScreen
{
private:
    SDL2pp::Renderer &renderer;
    SDL2pp::Texture title;
    SDL_Rect tint_rect;
    SDL_Rect title_src;
    SDL_Rect title_dst;

public:
    TableScreen(SDL2pp::Renderer &r, SDL2pp::Font &font) : renderer(r),
                                                           title(renderer, font.RenderText_Blended("Table", WHITE)),
                                                           tint_rect({0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT}),
                                                           title_src({0, 0, title.GetWidth(), title.GetHeight()}),
                                                           title_dst({(DEFAULT_WINDOW_WIDTH - title.GetWidth() / 2) / 2,
                                                                      50,
                                                                      title.GetWidth() / 2,
                                                                      title.GetHeight() / 2})
    {
    }

    void render_score(SDL2pp::Font &font, const UserTableSnapshot &users)
    {
        int base_y = title_dst.y + title_dst.h + 50;
        int text_spacing_y = 40;

        for (size_t index = 0; index < users.users.size(); index++)
        {
            std::string player_score = users.users[index].color_name + " " +
                                       "- Wins: " + std::to_string(users.users[index].round_wins);
            SDL2pp::Texture text(renderer, font.RenderText_Blended(player_score, WHITE));
            SDL_Rect text_src = {0, 0, text.GetWidth(), text.GetHeight()};
            SDL_Rect text_dst = {
                (DEFAULT_WINDOW_WIDTH - text.GetWidth() / 2) / 2,
                static_cast<int>(base_y + index * text_spacing_y),
                text.GetWidth() / 2,
                text.GetHeight() / 2};

            renderer.Copy(text, text_src, text_dst);
        }
    }

    void render(SDL2pp::Font &font, const UserTableSnapshot &users)
    {
        renderer.SetDrawBlendMode(SDL_BLENDMODE_BLEND);
        renderer.SetDrawColor(0, 0, 0, 128);
        renderer.FillRect(tint_rect);
        renderer.SetDrawColor(255, 255, 255, 255);
        renderer.SetDrawBlendMode(SDL_BLENDMODE_NONE);
        renderer.Copy(title, title_src, title_dst);
        render_score(font, users);
    }
};

#endif // TABLE_SCREEN_H