
#ifndef ACTIONS_H
#define ACTIONS_H

#include <cstdint>

enum Actions : uint8_t {
    RIGHT = 1,
    LEFT, // Enums are assigned consecutive values by default
    UP, // this number 3
    DOWN // 4
};

struct ActionMessage {
  uint8_t id;
  uint8_t action;
};

#endif //ACTIONS_H
