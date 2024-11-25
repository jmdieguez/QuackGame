#ifndef GUN_SIZE_FACTORY_H
#define GUN_SIZE_FACTORY_H

#include "../../../../../common/size.h"
#include "../../../../../common/texturefigure.h"

class GunSizeFactory
{
private:
    Size get_gun_size_to_texture(const TextureFigure &texture) const;

public:
    GunSizeFactory();
    Size get_size(const TextureFigure &texture) const;
    ~GunSizeFactory();
};

#endif // GUN_SIZE_FACTORY_H