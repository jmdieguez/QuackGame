#include "colorfactory.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/
ColorFactory::ColorFactory() {}

Color ColorFactory::Red() const { return Color(255, 0, 0); }
Color ColorFactory::Green() const { return Color(0, 255, 0); }
Color ColorFactory::Blue() const { return Color(0, 0, 255); }
Color ColorFactory::Yellow() const { return Color(255, 255, 0); }
Color ColorFactory::Cyan() const { return Color(0, 255, 255); }
Color ColorFactory::Magenta() const { return Color(255, 0, 255); }
Color ColorFactory::White() const { return Color(255, 255, 255); }
Color ColorFactory::Black() const { return Color(0, 0, 0); }
Color ColorFactory::Gray() const { return Color(128, 128, 128); }
Color ColorFactory::Orange() const { return Color(255, 165, 0); }

ColorFactory::~ColorFactory() {}