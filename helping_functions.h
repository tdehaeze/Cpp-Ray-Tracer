#ifndef DEF_HELPING_FUN
#define DEF_HELPING_FUN

#include <iostream>
#include <vector>
#include <cmath>

#include "Global.h"
#include "Vector.h"

namespace help_fun {
    double getFirstPositive(const std::vector<double> t);
    bool double_equals(double a, double b, double epsilon = 0.001);
    bool sort_ascending_order(double u, double v);
    Vector randomCos(const Vector normal);
}
#endif
