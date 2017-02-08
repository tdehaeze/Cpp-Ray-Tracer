#include "Sphere.h"

Sphere::Sphere(Vector orig, double rad, Vector mat, int mirr, int transp, double ind){
    origin = orig;
    radius = rad;
    mat.Normalize();
    material = mat;
    mirror = mirr;
    transparent = transp;
    indice = ind;
}

