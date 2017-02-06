#ifndef DEF_RAY
#define DEF_RAY

#include <string.h>
#include <math.h>
#include <algorithm>

#include "Vector.h"
#include "Sphere.h"
#include "Light.h"

class Ray {
public:
    Vector origin;
    Vector direction;
    Ray(Vector orig, Vector direct);
    double getIntersect(const Sphere sphere);
    double getIntensity(const Sphere sphere, double t, Light light);
    /* N'appelez cette fonction que si il y a une intersection */
    /* Vector getIntersect(const Sphere sphere); */
};

#endif
