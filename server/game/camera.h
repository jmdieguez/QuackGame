#ifndef SERVER_CAMERA_H
#define SERVER_CAMERA_H

#include <cstdint>
#include "../../common/snapshots.h"

#define PADDING 10 * TILE_SIZE

struct Camera {
    int x, y, width, height;
};

#endif // SERVER_CAMERA_H
