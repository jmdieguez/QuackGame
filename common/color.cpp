#include "color.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Color::Color()
{
}

Color::Color(int red, int green, int blue)
    : r(red), g(green), b(blue) {}

int Color::GetRed() const { return r; }

int Color::GetGreen() const { return g; }

int Color::GetBlue() const { return b; }

bool Color::operator==(const Color &other) const
{
    return r == other.r && g == other.g && b == other.b;
}

Color::~Color() {}