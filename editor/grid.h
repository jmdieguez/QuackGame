#ifndef EDITOR_GRID_H
#define EDITOR_GRID_H

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

#define TILE_SIZE 32

class Grid {
public:
    const int gridWidth = 16 ;
    const int gridHeight = 16;
    const int w_width = 1920;
    const int w_height = 1080;
    const int x = (w_width - (gridWidth * TILE_SIZE)) / 2;
    const int y = 50;

    Grid() {}
    ~Grid() {}

    void draw(Renderer &renderer) {
        renderer.SetDrawColor(255, 255, 255, 255);
        for (int row = 0; row <= gridHeight; ++row) {
            renderer.DrawLine(x, y + row * TILE_SIZE, x + gridWidth * TILE_SIZE, y + row * TILE_SIZE);
        }

        for (int col = 0; col <= gridWidth; ++col) {
            renderer.DrawLine(x + col * TILE_SIZE, y, x + col * TILE_SIZE, y + gridHeight * TILE_SIZE);
        }
    }

    bool contains(SDL_Point &p) {
        SDL_Rect rect = {x, y, gridWidth * TILE_SIZE, gridHeight * TILE_SIZE};
        return SDL_PointInRect(&p, &rect);
    }
};

#endif // EDITOR_GRID_H