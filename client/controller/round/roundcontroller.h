

#ifndef ROUNDCONTROLLER_H
#define ROUNDCONTROLLER_H

#include <iostream>
#include "../../../common/snapshots.h"
#include <SDL2pp/SDL2pp.hh>

class RoundController {
  SDL2pp::Renderer &renderer;
  SDL2pp::Font &font;
public:
  RoundController(SDL2pp::Renderer &renderer, SDL2pp::Font &font);
  void handle_round_change(const uint16_t& round, const std::vector<DuckScore> scores);
};



#endif //ROUNDCONTROLLER_H
