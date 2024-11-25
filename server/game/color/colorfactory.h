#ifndef COLOR_FACTORY_H
#define COLOR_FACTORY_H

#include "../../../common/color.h"

class ColorFactory
{
private:
public:
    ColorFactory();

    Color Red() const;
    Color Green() const;
    Color Blue() const;
    Color Yellow() const;
    Color Cyan() const;
    Color Magenta() const;
    Color White() const;
    Color Black() const;
    Color Gray() const;
    Color Orange() const;

    ~ColorFactory();
};

#endif // COLOR_FACTORY_H