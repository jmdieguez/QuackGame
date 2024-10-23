//
//
// Created by trini-taller on 10/21/24.
//

#ifndef SNAPSHOTS_H
#define SNAPSHOTS_H

#include <cstdint>
#include <vector>

#include "duck_actions.h"
#include "gun_type.h"

class PositionSnapshot {
public:
  uint16_t pos_x;
  uint16_t pos_y;

  PositionSnapshot(uint16_t &x, uint16_t &y) : pos_x(x), pos_y(y) {}
  ~PositionSnapshot() {}
};

class GunSnapshot {
public:
  const GunType type;
  const uint8_t rounds;
  const uint8_t range;
  GunSnapshot(GunType &t, uint8_t &r, uint8_t &rng) : type(t), rounds(r), range(rng) {}
};

class DuckSnapshot {
public:
  const uint8_t id;
  const PositionSnapshot &position;
  const DuckAction &current_action;
  const bool shooting;
  const bool looking_right;
  const bool looking_up;
  const bool has_chestplate;
  const bool has_helmet;
  const bool is_alive;
  const GunSnapshot &gun;

  DuckSnapshot(const uint8_t &i,
               const PositionSnapshot &p_snap,
               const DuckAction &a,
               const bool &sh,
               const bool &looking_r,
               const bool &looking_u,
               const bool &has_c,
               const bool &has_h,
               const bool &is_al,
               const GunSnapshot &g_snap) :
          id(i),
          position(p_snap),
          current_action(a),
          shooting(sh),
          looking_right(looking_r),
          looking_up(looking_u),
          has_chestplate(has_c),
          has_helmet(has_h),
          is_alive(is_al),
          gun(g_snap) {}
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
  MapSnapshot(const uint16_t &s_x, const uint16_t &s_y) : size_x(s_x), size_y(s_y) {}
  ~MapSnapshot() {}
};

class Snapshot {
public:
  const std::vector<DuckSnapshot> ducks;
  const MapSnapshot map;

  Snapshot(std::vector<DuckSnapshot> &&d_s, MapSnapshot &&m) : ducks(d_s), map(m) {}
};

#endif //SNAPSHOTS_H
