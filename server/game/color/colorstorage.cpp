#include <algorithm>
#include "colorstorage.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

ColorStorage::ColorStorage()
{
    ColorFactory factory;
    availableColors.push_back(factory.Red());
    availableColors.push_back(factory.Green());
    availableColors.push_back(factory.Blue());
    availableColors.push_back(factory.Yellow());
    availableColors.push_back(factory.Cyan());
    availableColors.push_back(factory.Magenta());
    availableColors.push_back(factory.White());
    availableColors.push_back(factory.Black());
    availableColors.push_back(factory.Gray());
    availableColors.push_back(factory.Orange());
}

Color ColorStorage::get_color()
{
    Color color = availableColors.front();
    availableColors.erase(availableColors.begin());
    usedColors.push_back(color);
    return color;
}

void ColorStorage::return_color(const Color &color)
{
    auto it = std::find(usedColors.begin(), usedColors.end(), color);
    if (it == usedColors.end())
        return;
    usedColors.erase(it);
    availableColors.push_back(color);
}

ColorStorage::~ColorStorage()
{
}
