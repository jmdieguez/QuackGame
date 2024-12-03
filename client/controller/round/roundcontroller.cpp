
#include "roundcontroller.h"
#include "../render/transitionmanager.h"

RoundController::RoundController(RenderStorage &render_storage, SDL2pp::Renderer &renderer, SDL2pp::Font &font, bool &is_showing_table, bool &finish_showing_table)
    : render_storage(render_storage), renderer(renderer), font(font), table_screen(renderer, font),
      is_showing_table(is_showing_table), finish_showing_table(finish_showing_table), it(0) {}

void RoundController::handle_round_change(const uint16_t &round, const std::vector<DuckScore> scores)
{
    it++;
    finish_showing_table = false;
    is_showing_table = true;
    if (it % 100 == 0)
    {
        is_showing_table = false;
        finish_showing_table = false;
        it = 0;
        return;
    }
    render_storage.get_scene().render();
    table_screen.render(font, scores);
}