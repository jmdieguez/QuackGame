//
//
// Created by trini-taller on 10/21/24.
//

#ifndef SNAPSHOTS_H
#define SNAPSHOTS_H

#include <cstdint>
#include <vector>

struct Position {
    uint8_t pos_x;
    uint8_t pos_y;
};

struct Duck {
  uint8_t pos_x;
  uint8_t pos_y;  // por simplicidad temporal voy a manejarlo asi en vez Position
  uint8_t id;
  uint8_t action;
};

struct Gun {
  uint8_t id;
  uint8_t ammo;
  uint8_t range;
};

struct Box {
  Position pos;
  Gun gun;
};

struct Snapshot {
  std::vector<Duck> ducks;
  // Box boxes[]
};
#endif //SNAPSHOTS_H
