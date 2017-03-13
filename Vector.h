#ifndef DEF_VECTOR
#define DEF_VECTOR

#include <vector>
#include <cmath> 
#include <cstring> // for memcpy()
#include <iostream>
#include "global.h"

class Vector {
public:
    /* Constructeur */
    Vector(double x = 0, double y = 0, double z = 0);

    /* Constructeur de copie */
    Vector(const Vector& b);

    /* Getter */
    double getX() const;
    double getY() const;
    double getZ() const;

    /* Opérateurs racourcis */
    Vector& operator+=(const Vector& a);
    Vector& operator-=(const Vector& a);
    bool operator==(const Vector& a) const;

    friend std::ostream& operator<<(std::ostream &out, const Vector &v);

    double operator[](int i) const;
    double norm() const;
    double squaredNorm() const;

    void Normalize();

protected:
    double xyz[3];
};

Vector operator+(const Vector& a,const Vector& b);
Vector operator-(const Vector& a,const Vector& b);
Vector operator-(const Vector& a);
Vector operator*(const double a, const Vector& b);
double operator*(const Vector& a, const Vector& b);
Vector operator^(const Vector& a, const Vector& b);
Vector operator/(const Vector& a, const double b);

#endif
