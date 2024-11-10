#ifndef SIZE_H
#define SIZE_H

#include <cstdint>

class Size
{
public:
    uint16_t width;
    uint16_t height;

    explicit Size(const uint16_t &width, const uint16_t &height) : width(width), height(height) {};
    ~Size() {};
};

#endif // SIZE_H