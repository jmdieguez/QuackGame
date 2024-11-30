#ifndef COLOR_FACTORY_H
#define COLOR_FACTORY_H

#include <string>
#include <utility>
#include "../../../common/color.h"

class ColorFactory
{
private:
public:
    ColorFactory();
    Color red() const;
    Color green() const;
    Color blue() const;
    Color yellow() const;
    Color cyan() const;
    Color magenta() const;
    Color white() const;
    Color black() const;
    Color gray() const;
    Color orange() const;
    ~ColorFactory();
};

#endif // COLOR_FACTORY_H