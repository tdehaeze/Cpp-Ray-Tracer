#include "Vector.h"

using namespace std;

Vector::Vector(double x, double y, double z){
    xyz[0] = x;
    xyz[1] = y;
    xyz[2] = z;
}
Vector::Vector(const Vector& b){
    memcpy(xyz,b.xyz,3*sizeof(double));
}
double Vector::operator[](int i) const{
    return xyz[i];
}
double Vector::norm(){
    return sqrt(xyz[0]*xyz[0] + xyz[1]*xyz[1] + xyz[2]*xyz[2]);
}
double Vector::squaredNorm(){
    return xyz[0]*xyz[0] + xyz[1]*xyz[1] + xyz[2]*xyz[2];
}
void Vector::Normalize(){
    double n = sqrt(squaredNorm());
    xyz[0] /= n;
    xyz[1] /= n;
    xyz[2] /= n;
}

Vector operator+( Vector const& a,Vector const& b){
    return Vector(a[0]+b[0] , a[1]+b[1] , a[2]+b[2]);
}
Vector operator-(const Vector& a,const Vector& b){
    return Vector(a[0]-b[0] , a[1]-b[1] , a[2]-b[2]);
}
Vector operator-(const Vector& a){
    return Vector(-a[0] , -a[1] , -a[2]);
}
Vector operator*(const double a, const Vector& b){
    return Vector(a*b[0], a*b[1], a*b[2]);
}
double operator*(const Vector& a, const Vector& b){
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}
Vector operator^(const Vector& a, const Vector& b){
    return Vector(a[1]*b[2]-a[2]*b[1], -a[0]*b[2]+a[2]*b[0], a[0]*b[1]-a[1]*b[0]);
}
Vector operator/(const Vector& a, const double b){
    return Vector(a[0]/b, a[1]/b, a[2]/b);
}
