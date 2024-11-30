#include "colorfactory.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/
ColorFactory::ColorFactory() {}

Color ColorFactory::red() const { return Color(255, 0, 0, "Red"); }
Color ColorFactory::green() const { return Color(0, 255, 0, "Green"); }
Color ColorFactory::blue() const { return Color(0, 0, 255, "Blue"); }
Color ColorFactory::yellow() const { return Color(255, 255, 0, "Yellow"); }
Color ColorFactory::cyan() const { return Color(0, 255, 255, "Cyan"); }
Color ColorFactory::magenta() const { return Color(255, 0, 255, "Magenta"); }
Color ColorFactory::white() const { return Color(255, 255, 255, "White"); }
Color ColorFactory::black() const { return Color(0, 0, 0, "Black"); }
Color ColorFactory::gray() const { return Color(128, 128, 128, "Gray"); }
Color ColorFactory::orange() const { return Color(255, 165, 0, "Orange"); }

ColorFactory::~ColorFactory() {}