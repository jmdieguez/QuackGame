

#ifndef ROUNDCONTROLLER_H
#define ROUNDCONTROLLER_H

#include <iostream>
#include "../render/renderstorage.h"
#include "../../view/table_screen.h"
#include "../../../common/snapshots.h"
#include <SDL2pp/SDL2pp.hh>

class RoundController
{
    RenderStorage &render_storage;
    SDL2pp::Renderer &renderer;
    SDL2pp::Font &font;
    TableScreen table_screen;
    bool &is_showing_table;
    bool &finish_showing_table;
    size_t it;

public:
    RoundController(RenderStorage &render_storage, SDL2pp::Renderer &renderer, SDL2pp::Font &font, bool &is_showing_table, bool &finish_showing_table);
    void handle_round_change(const uint16_t &round, const std::vector<DuckScore> scores);
};

#endif // ROUNDCONTROLLER_H
