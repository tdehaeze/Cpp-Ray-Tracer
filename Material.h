#ifndef DEF_MATERIAL
#define DEF_MATERIAL

#include <string.h>
#include <math.h>

#include "Vector.h"

class Material {
public:
    Vector colors;
    Material(Vector colors_init);
};

#endif
