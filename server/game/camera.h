#ifndef SERVER_CAMERA_H
#define SERVER_CAMERA_H

#include <cstdint>
#include "../../common/snapshots.h"

#define PADDING 10 * TILE_SIZE
#define MIN_CAMERA_WIDTH  4 * TILE_SIZE
#define MIN_CAMERA_HEIGHT MIN_CAMERA_WIDTH * 9 / 16

struct Camera {
    uint16_t x, y, width, height;
};

#endif // SERVER_CAMERA_H
