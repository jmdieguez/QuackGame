#include <algorithm>
#include "colorstorage.h"

/***************************************************************************
                              PUBLIC METHODS
****************************************************************************/

ColorStorage::ColorStorage()
{
    ColorFactory factory;
    availableColors.push_back(factory.red());
    availableColors.push_back(factory.green());
    availableColors.push_back(factory.blue());
    availableColors.push_back(factory.yellow());
    availableColors.push_back(factory.cyan());
    availableColors.push_back(factory.magenta());
    availableColors.push_back(factory.white());
    availableColors.push_back(factory.black());
    availableColors.push_back(factory.gray());
    availableColors.push_back(factory.orange());
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
