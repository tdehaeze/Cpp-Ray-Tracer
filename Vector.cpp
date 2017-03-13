#include "Vector.h"

Vector::Vector(double x, double y, double z)
    : xyz{x, y, z} {}
    
Vector::Vector(const Vector& b){
    std::memcpy(xyz,b.xyz,3*sizeof(double));
}

double Vector::operator[](int i) const{
    return xyz[i];
}

double Vector::norm() const{
    return std::sqrt(xyz[0]*xyz[0] + xyz[1]*xyz[1] + xyz[2]*xyz[2]);
}

double Vector::squaredNorm() const{
    return xyz[0]*xyz[0] + xyz[1]*xyz[1] + xyz[2]*xyz[2];
}

void Vector::Normalize(){
    double n = std::sqrt(squaredNorm());
    xyz[0] /= n;
    xyz[1] /= n;
    xyz[2] /= n;
}

double Vector::getX() const{
    return xyz[0];
}

double Vector::getY() const{
    return xyz[1];
}

double Vector::getZ() const{
    return xyz[2];
}

Vector operator+(const Vector& a,const Vector& b){
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

bool Vector::operator==(const Vector& a) const{
    return ( this->xyz[0] == a.getX() && this->xyz[1] == a.getY() && this->xyz[2] == a.getZ() );
}

Vector& Vector::operator+=(const Vector& a){
    this->xyz[0] += a.getX();
    this->xyz[1] += a.getY();
    this->xyz[2] += a.getZ();
    return *this;
}

Vector& Vector::operator-=(const Vector& a){
    this->xyz[0] -= a.getX();
    this->xyz[1] -= a.getY();
    this->xyz[2] -= a.getZ();
    return *this;
}
