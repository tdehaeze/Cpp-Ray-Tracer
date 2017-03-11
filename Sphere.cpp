#include "Sphere.h"

Sphere::Sphere(Vector m_origin, double m_radius, Material* m_material)
    : Object(m_material), origin(m_origin), radius(m_radius) {}

Sphere::~Sphere(){

}

Vector Sphere::getOrigin() const{
    return origin;
}

double Sphere::getRadius() const{
    return radius;
}

Vector Sphere::getCenter() const{
    return origin;
}

Vector* Sphere::getNormal(Ray rayon) const{
    double t = getDistance(rayon);
    if (t > 0) {
        Vector* intersect_normal = new Vector(rayon.getOrigin() + t*rayon.getDirection() - origin);
        intersect_normal->Normalize();
        return intersect_normal;
    } else {
        return 0;
    }
}

double Sphere::getDistance(Ray rayon) const{
    double t;

    Vector CO = rayon.getOrigin() - this->getOrigin();

    double a = 1;
    double b = 2*rayon.getDirection()*CO;
    double c = CO.squaredNorm() - this->getRadius()*this->getRadius();

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
        t1 = (-b+std::sqrt(delta))/(2*a);
        t2 = (-b-std::sqrt(delta))/(2*a);
        if (t1 > 0 && t2 > 0) {
            t = std::min(t1, t2);
        } else if (t1*t2 < 0) {
            t = std::max(t1, t2);
        } else {
            t = -1;
        }
    }

    return t;
}

bool Sphere::isInside(Vector point) const{
    return (std::pow(point.getX()-origin.getX(), 2) + std::pow(point.getX()-origin.getX(),2) + std::pow(point.getX()-origin.getX(), 2) < radius);
}

