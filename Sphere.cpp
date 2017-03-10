#include "Sphere.h"

Sphere::Sphere(Vector m_origin, double m_radius, Material* m_material)
    : Object(), origin(m_origin), radius(m_radius), material(m_material) {}

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

Material* Sphere::getMaterial() const{
    return material;
}

Vector* Sphere::getIntersect(Ray rayon) const{
    double t = getDistance(rayon);
    if (t > 0) {
        Vector* intersect_point = new Vector(rayon.getOrigin() + t*rayon.getDirection());
        return intersect_point;
    } else {
        return 0;
    }
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

Vector Sphere::getPointBeforeIntersect(Ray rayon) const{
    Vector point_before_intersect = *this->getIntersect(rayon);
    Vector intersect_normal = *this->getNormal(rayon);

    if (intersect_normal*rayon.getDirection() > 0) { /* we are inside the sphere and going outside */
        point_before_intersect -= 0.01*intersect_normal;
    } else { /* we are outside the sphere and comming inside */
        point_before_intersect += 0.01*intersect_normal;
    }

    return point_before_intersect;
}

Vector Sphere::getPointAfterIntersect(Ray rayon) const{
    Vector point_after_intersect = *this->getIntersect(rayon);
    Vector intersect_normal = *this->getNormal(rayon);

    if (intersect_normal*rayon.getDirection() > 0) { /* we are inside the sphere and going outside */
        point_after_intersect += 0.01*intersect_normal;
    } else { /* we are outside the sphere and comming inside */
        point_after_intersect -= 0.01*intersect_normal;
    }

    return point_after_intersect;
}

Ray Sphere::getReflectedRay(Ray rayon) const{
    Vector n = *this->getNormal(rayon);
    Vector i = rayon.getDirection();

    Vector reflected_vector = i - 2*(i*n)*n;

    return Ray(this->getPointBeforeIntersect(rayon), reflected_vector);
}

Ray Sphere::getRefractedRay(Ray rayon, double ind_before, double ind_after) const{
    Vector n = *this->getNormal(rayon);
    Vector i = rayon.getDirection();

    /* if (n*i > 0){ /1* inside object to outside *1/ */
    /*     n = -n; */
    /* } */

    double ind_frac = ind_before/ind_after;

    Vector refracted_direction = ind_frac*i - (-ind_frac*std::abs(n*i) + std::sqrt(1-ind_frac*ind_frac*(1 - (n*i)*(n*i))))*n;
    refracted_direction.Normalize();

    return Ray(this->getPointAfterIntersect(rayon), refracted_direction);
}

