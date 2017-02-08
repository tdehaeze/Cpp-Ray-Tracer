#include "Sphere.h"

Sphere::Sphere(Vector orig, double rad, Vector mat, int secul){
    origin = orig;
    radius = rad;
    mat.Normalize();
    material = mat;
    seculaire = secul;
}

