#ifndef DEF_SPHERE
#define DEF_SPHERE

#include <math.h>
#include <string.h>

#include "Vector.h"
#include "Material.h"

class Sphere {
public:
    Vector origin;
    double radius;
    Vector material;
    int mirror;
    int transparent;
    double indice;
    Sphere(Vector orig, double rad, Vector mat, int mirr, int transp, double ind);
};

#endif
