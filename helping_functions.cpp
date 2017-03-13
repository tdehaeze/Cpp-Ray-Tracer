#include "helping_functions.h"

double getFirstPositive(const std::vector<double> t){
    for(const double &element : t) {
        if (element > 0) {
            return element;
        }
    }
    return -1;
}

bool double_equals(double a, double b, double epsilon){
    return std::abs(a - b) < epsilon;
}

bool sort_ascending_order(double u, double v){
   return u < v;
}
