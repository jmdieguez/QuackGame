#include "color.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

Color::Color()
{
}

Color::Color(int red, int green, int blue) : r(red), g(green), b(blue) {}

Color::Color(int red, int green, int blue, std::string text)
    : r(red), g(green), b(blue), text(text) {}

int Color::get_red() const { return r; }

int Color::get_green() const { return g; }

int Color::get_blue() const { return b; }

std::string Color::get_text() const
{
    return text;
}

bool Color::operator==(const Color &other) const
{
    return r == other.r && g == other.g && b == other.b;
}

Color::~Color() {}