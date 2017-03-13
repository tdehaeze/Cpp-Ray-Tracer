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

Vector* Sphere::getNormal(Ray rayon) const{
    std::vector<double> t = this->getIntersections(rayon);

    double first_positive = this->getFirstPositive(t);

    if (first_positive > 0) {
        Vector* intersect_normal = new Vector(rayon.getOrigin() + first_positive*rayon.getDirection() - this->getOrigin());
        intersect_normal->Normalize();
        return intersect_normal;
    } else {
        return 0;
    }
}

std::vector<double> Sphere::getIntersections(const Ray rayon) const{
    std::vector<double> t;

    Vector CO = rayon.getOrigin() - this->getOrigin();

    double a = 1;
    double b = 2*rayon.getDirection()*CO;
    double c = CO.squaredNorm() - this->getRadius()*this->getRadius();

    double delta = b*b - 4*a*c;

    if (delta == 0) {
        t.push_back(-b/(2*a));
    } else if (delta > 0){
        t.push_back(-b+std::sqrt(delta));
        t.push_back(-b-std::sqrt(delta));
    }

    std::sort(t.begin(), t.end(), std::greater<int>());

    return t;
}

/* 
 * TODO : vérifier le bon fonctionnement
 * */
bool Sphere::isInside(Vector point) const{
    return (std::pow(point.getX()-this->getOrigin().getX(), 2) + std::pow(point.getY()-this->getOrigin().getY(),2) + std::pow(point.getZ()-this->getOrigin().getZ(), 2) < std::pow(radius,2));
}

