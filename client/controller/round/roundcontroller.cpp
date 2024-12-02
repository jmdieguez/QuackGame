
#include "roundcontroller.h"
#include "../render/transitionmanager.h"

RoundController::RoundController(SDL2pp::Renderer &renderer, SDL2pp::Font &font)
    : renderer(renderer), font(font) {}

void RoundController::handle_round_change(const uint16_t& round, const std::vector<DuckScore> scores) {
    if (round % 5 != 0) {
        TransitionManager transitionManager(renderer, font);
        transitionManager.fade_transition();
    } // else {
        // muetra la tabla
    // }
}