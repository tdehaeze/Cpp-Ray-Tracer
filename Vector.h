#ifndef DEF_VECTOR
#define DEF_VECTOR

#include <vector>
#include <math.h>

class Vector {
public:
    double xyz[3];

    Vector(double x = 0, double y = 0, double z = 0);
    Vector(const Vector& b);
    double operator[](int i) const;
    double norm();
    double squaredNorm();
    void Normalize();
};

Vector operator+( Vector const& a,Vector const& b);
Vector operator-(const Vector& a,const Vector& b);
Vector operator-(const Vector& a);
Vector operator*(const double a, const Vector& b);
double operator*(const Vector& a, const Vector& b);
Vector operator^(const Vector& a, const Vector& b);
Vector operator/(const Vector& a, const double b);

#endif
