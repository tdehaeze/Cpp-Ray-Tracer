#include "Vector.h"

using namespace std;


Vector::Vector(double x, double y, double z) : xyz[0] = x, xyz[1] = y, xyz[2] = z {

}
/* Vector::Vector(double x, double y, double z){ */
/*     xyz[0] = x; */
/*     xyz[1] = y; */
/*     xyz[2] = z; */
/* } */
Vector::Vector(const Vector& b){
    memcpy(xyz,b.xyz,3*sizeof(double));
}
double Vector::operator[](int i) const{
    return xyz[i];
}
double Vector::norm() const{
    return sqrt(xyz[0]*xyz[0] + xyz[1]*xyz[1] + xyz[2]*xyz[2]);
}
double Vector::squaredNorm() const{
    return xyz[0]*xyz[0] + xyz[1]*xyz[1] + xyz[2]*xyz[2];
}
void Vector::Normalize(){
    double n = sqrt(squaredNorm());
    xyz[0] /= n;
    xyz[1] /= n;
    xyz[2] /= n;
}


double getX(const Vector& v) {
    return v[0];
}

double getY(const Vector& v) {
    return v[1];
}

double getZ(const Vector& v) {
    return v[2];
}

Vector operator+( Vector const& a,Vector const& b){
    return Vector(a.getX()+b.getX() , a.getY()+b.getY() , a.getZ()+b.getZ());
}
Vector operator-(const Vector& a,const Vector& b){
    return Vector(a.getX()-b.getX() , a.getY()-b.getY() , a.getZ()-b.getZ());
}
Vector operator-(const Vector& a){
    return Vector(-a.getX() , -a.getY() , -a.getZ());
}
Vector operator*(const double a, const Vector& b){
    return Vector(a*b.getX(), a*b.getY(), a*b.getZ());
}
double operator*(const Vector& a, const Vector& b){
    return a.getX()*b.getX() + a.getY()*b.getY() + a.getZ()*b.getZ();
}
Vector operator^(const Vector& a, const Vector& b){
    return Vector(a.getY()*b.getZ()-a.getZ()*b.getY(), -a.getX()*b.getZ()+a.getZ()*b.getX(), a.getX()*b.getY()-a.getY()*b.getX());
}
Vector operator/(const Vector& a, const double b){
    return Vector(a.getX()/b, a.getY()/b, a.getZ()/b);
}
