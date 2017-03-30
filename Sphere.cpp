#include "Sphere.h"

extern std::default_random_engine engine;
extern std::uniform_real_distribution <double> distrib;

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

Vector Sphere::getNormal(Ray rayon) const{
    double first_positive = help_fun::getFirstPositive(this->getIntersections(rayon));

    if (first_positive > 0) {
        Vector intersect_normal = Vector(rayon.getOrigin() + first_positive*rayon.getDirection() - this->getOrigin());
        intersect_normal.Normalize();
        return intersect_normal;
    } else {
        return Vector(0, 0, 0);
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
        t.push_back((-b+std::sqrt(delta))/(2*a));
        t.push_back((-b-std::sqrt(delta))/(2*a));
    }

    std::sort(t.begin(), t.end(), std::less<double>());

    /* if (t.size() == 2) { */
        /* std::cout << "T0 = " << t[0] << "T1 = " << t[1] << std::endl; */
    /* } */

    return t;
}

bool Sphere::isInside(Vector point) const{
    return (std::pow(point.getX()-this->getOrigin().getX(), 2) + std::pow(point.getY()-this->getOrigin().getY(),2) + std::pow(point.getZ()-this->getOrigin().getZ(), 2) < std::pow(radius,2));
}

Vector Sphere::getRandomPoint() const{
    Vector point = this->getOrigin() + this->getRadius()*Vector(2*(distrib(engine)-0.5), 2*(distrib(engine)-0.5), 2*(distrib(engine)-0.5));

    while(!this->isInside(point)) {
        point = this->getOrigin() + this->getRadius()*Vector(distrib(engine), distrib(engine), distrib(engine));
    }
    
    return point;


    /* double a1 = distrib(engine); */
    /* double a2 = distrib(engine); */

    /* double cos_alpha = 1 - a1 + a1*std::sqrt(1-std::pow(this->getRadius()/(intersection - this->getOrigin()).norm(), 2)); */
    /* double sin_alpha = std::sqrt(1 - std::pow(cos_alpha, 2)); */
    /* double phi = 2*M_PI*a2; */

    /* Vector random = Vector(std::cos(phi)*sin_alpha, sin(phi)*sin_alpha, cos_alpha); */

    /* Vector u = this->getOrigin() - intersection; */
    /* u.Normalize(); */
    /* Vector v = u^Vector(1, 0, 0); */
    /* Vector w = u^v; */

    /* double d0 = u[0]*random[0] + v[0]*random[1] + w[0]*random[2]; */
    /* double d1 = u[1]*random[0] + v[1]*random[1] + w[1]*random[2]; */
    /* double d2 = u[2]*random[0] + v[2]*random[1] + w[2]*random[2]; */

    /* return Ray(intersection, Vector(d0, d1, d2)); */
}


