#ifndef PROJECTILE_SIZE_FACTORY_H
#define PROJECTILE_SIZE_FACTORY_H

#include "../../../../../common/size.h"
#include "../../../../../common/texturefigure.h"

class ProjectileSizeFactory
{
private:
    Size texture_to_projectile_size(const TextureFigure &texture) const;

public:
    ProjectileSizeFactory();
    Size get_size(const TextureFigure &texture) const;
    ~ProjectileSizeFactory();
};

#endif // PROJECTILE_SIZE_FACTORY_H