#ifndef DEF_LIGHT
#define DEF_LIGHT

#include <math.h>
#include "Vector.h"

class Light {
public:
    Vector origin;
    double intensity;
    Light(Vector orig, double intens);
};

#endif
