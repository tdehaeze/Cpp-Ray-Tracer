#include "Sphere.h"

Sphere::Sphere(Vector orig, double rad, Vector mat){
    origin = orig;
    radius = rad;
    mat.Normalize();
    material = mat;
}

