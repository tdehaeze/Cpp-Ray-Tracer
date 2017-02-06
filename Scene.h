#ifndef DEF_SCENE
#define DEF_SCENE

#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>

#include "Vector.h"
#include "Sphere.h"
#include "Ray.h"

class Scene {
public:
    std::vector<Sphere> spheres;
    Scene();
    void addSphere(const Sphere sphere);
    Sphere getSphere(Ray ray);
    /* double getIntensity(const Sphere sphere, double t, Light light); */
};

#endif
