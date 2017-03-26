#include "helping_functions.h"

extern std::default_random_engine engine;
extern std::uniform_real_distribution <double> distrib;

double help_fun::getFirstPositive(const std::vector<double> t){
    for(const double &element : t) {
        if (element > 0.) {
            return element;
        }
    }
    return -1;
}

bool help_fun::double_equals(double a, double b, double epsilon){
    return std::abs(a - b) < epsilon;
}

bool help_fun::sort_ascending_order(double u, double v){
   return u < v;
}

Vector help_fun::randomCos(const Vector normal){
    double u = distrib(engine);
    double v = distrib(engine);

    double x = cos(2*M_PI*u)*sqrt(1-v);
    double y = sin(2*M_PI*u)*sqrt(1-v);
    double z = sqrt(v);

    Vector r1(distrib(engine), distrib(engine), distrib(engine));
    r1.Normalize();

    Vector u1 = normal^r1;
    Vector u2 = normal^u1;

    return x*u1 + y*u2 + z*normal;
}

