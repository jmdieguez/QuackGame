//
//
// Created by trini-taller on 10/21/24.
//

#ifndef SNAPSHOTS_H
#define SNAPSHOTS_H

#include <cstdint>
#include <vector>

#include "duck.h"
#include "gun_type.h"

class PositionSnapshot {
public:
    uint8_t pos_x;
    uint8_t pos_y;

    // Cambiar a paso por valor
    PositionSnapshot(uint8_t x, uint8_t y) : pos_x(x), pos_y(y) {}
    ~PositionSnapshot() {}
};


class GunSnapshot
{
public:
  const GunType type;
  const uint8_t rounds;
  const uint8_t range;
  const uint8_t ammo;

  GunSnapshot(const GunType& t, const uint8_t& r, const uint8_t& rng, const uint8_t& ammo):
  type(t), rounds(r), range(rng), ammo(ammo) {}
};

class DuckSnapshot {
public:
  const uint16_t id;
  //const uint16_t health;
  const PositionSnapshot position;
  const DuckAction& current_action;
 // const DuckStatus& status;
  //const GunSnapshot& gun;

  explicit DuckSnapshot(const uint16_t& i, PositionSnapshot p_snap, const DuckAction& action) :
   id(i),
   position(std::move(p_snap)),
   current_action(action) {}
};

class BoxSnapshot {
public:
  const PositionSnapshot &pos;
  const GunSnapshot &gun;

  BoxSnapshot(PositionSnapshot &p, GunSnapshot &g) : pos(p), gun(g) {}
};

class MapSnapshot {
public:
  const uint16_t size_x;
  const uint16_t size_y;
  std::vector<BoxSnapshot> boxes;

  MapSnapshot(const uint16_t& s_x, const uint16_t& s_y) : size_x(s_x), size_y(s_y) {}
  ~MapSnapshot() {}
};

class Snapshot
{
public:
  std::vector<DuckSnapshot> ducks;
  void add_duck(uint16_t id, PositionSnapshot pos) {
    DuckSnapshot duck(id, pos);
    ducks.emplace_back(duck);
  }
   Snapshot() : ducks({}) {}
  Snapshot(std::vector<DuckSnapshot>&& d_s) : ducks(d_s) {}
};

#endif // SNAPSHOTS_H
