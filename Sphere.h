#ifndef DEF_SPHERE
#define DEF_SPHERE

#include <math.h>
#include <string.h>
#include "Vector.h"

class Sphere {
public:
    Vector origin;
    double radius;
    Sphere(Vector orig, double rad);
};

#endif
