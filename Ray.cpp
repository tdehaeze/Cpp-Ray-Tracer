#include "Ray.h"

Ray::Ray(Vector orig, Vector direct){
    origin = orig;
    direction = direct;
}

/* get if the ray is crossing the sphere one time or two times or not at all */
double Ray::getDistanceToSphere(const Sphere sphere){
    double t;

    Vector CO = origin - sphere.origin;

    double a = 1;
    double b = 2*direction*CO;
    double c = CO.squaredNorm() - sphere.radius*sphere.radius;

    double delta = b*b - 4*a*c;

    double t1 = 0;
    double t2 = 0;

    if (delta < 0) {
        t = -1;
    } else if (delta == 0){
        t1 = -b/(2*a);
        if (t1 > 0) {
            t = t1;
        } else {
            t = -1;
        }
    } else {
        t1 = (-b+sqrt(delta))/(2*a);
        t2 = (-b-sqrt(delta))/(2*a);
        if (t1 > 0 && t2 > 0) {
            t = std::min(t1, t2);
        } else if ((t1 < 0 && t2 > 0) || (t1 > 0 && t2 < 0)) {
            t = std::max(t1, t2);
        } else {
            t = -1;
        }
    }

    return t;
}

double Ray::getIntensity(const Sphere sphere, double t, Light light){
    double intensity;

    Vector l = light.origin - (origin + t * direction);
    l.Normalize();
    Vector n = origin + t * direction - sphere.origin;
    n.Normalize();

    double d1 = (origin + t * direction).norm();
    double d2 = (light.origin - (origin + t * direction)).norm();

    intensity = std::max(0.0, l*n)*light.intensity/((d1 + d2)*(d1+d2));

    return intensity;
}

