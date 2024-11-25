#ifndef COLOR_STORAGE_H
#define COLOR_STORAGE_H

#include "colorfactory.h"
#include <vector>
#include <cstdint>

class ColorStorage
{
private:
    std::vector<Color> availableColors;
    std::vector<Color> usedColors;

public:
    ColorStorage();
    Color get_color();
    void return_color(const Color &color);
    ~ColorStorage();
};

#endif // COLOR_STORAGE_H
