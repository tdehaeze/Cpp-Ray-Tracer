#include "Cylindre.h"

Cylindre::Cylindre(Vector m_a, Vector m_b, double m_radius, Material* m_material)
    : Object(m_material), a(m_a), b(m_b), radius(m_radius) {}

Cylindre::~Cylindre(){

}

Vector Cylindre::getA() const{
    return a;
}

Vector Cylindre::getB() const{
    return b;
}

double Cylindre::getRadius() const{
    return radius;
}

Vector Cylindre::getDirection() const{
    Vector direction = (b-a);
    direction.Normalize();
    return direction;
}

Vector Cylindre::getNormalA() const{
    Vector normal_a = (this->getA()-this->getB());
    normal_a.Normalize();
    return normal_a;
}

Vector Cylindre::getNormalB() const{
    Vector normal_b = (this->getB()-this->getA());
    normal_b.Normalize();
    return normal_b;
}

Vector Cylindre::getCenter() const{
    return (a+b)/2;
}

double Cylindre::getDistanceToPlanA(Ray rayon) const{
    double t = -1;

    if (rayon.getDirection()*this->getNormalA() != 0) {
        t = ((this->getA()-rayon.getOrigin())*this->getNormalA())/(rayon.getDirection()*this->getNormalA());
        if (t < 0)
            t = -1;
    }

    return t;
}

double Cylindre::getDistanceToPlanB(Ray rayon) const{
    double t = -1;

    if (rayon.getDirection()*this->getNormalB() != 0) {
        t = ((this->getB()-rayon.getOrigin())*this->getNormalB())/(rayon.getDirection()*this->getNormalB());
        if (t < 0)
            t = -1;
    }

    return t;
}

double Cylindre::getDistanceToCylindre(Ray rayon) const{
    std::pair<double, double> t1t2 = this->getT1T2(rayon);
    return t1t2.first;
}

std::pair<double, double> Cylindre::getT1T2(Ray rayon) const{
    Vector u = this->getDirection();
    Vector v = rayon.getDirection();
    Vector OA = rayon.getOrigin() - this->getA();
    double R = this->getRadius();

    double a = (v-(v*u)*u)*(v-(v*u)*u);
    double b = 2*(v-(v*u)*u)*(OA-(OA*u)*u);
    double c = (OA-(OA*u)*u)*(OA-(OA*u)*u)-R*R;

    double delta = b*b - 4*a*c;

    double t1 = -1;
    double t2 = -1;

    if (delta == 0 && -b/(2*a) > 0){
        t1 = -b/(2*a);
    } else if (delta > 0) {
        t1 = (-b+std::sqrt(delta))/(2*a);
        t2 = (-b-std::sqrt(delta))/(2*a);
    }

    if (t1 > t2)
        std::swap(t1, t2);

    return std::make_pair(t1, t2);
}

double Cylindre::getDistance(Ray rayon) const{
    double t = -1;
 
    std::pair<double, double> t1t2 = this->getT1T2(rayon);

    double t1 = t1t2.first;
    double t2 = t1t2.second;


    if (t1 > 0.) {
        double s1 = this->getDistanceToPlanA(rayon);
        double s2 = this->getDistanceToPlanB(rayon);
        if (s1 > s2)
            std::swap(s1, s2);

        if (t1 >= s1 && t1 <= s2) {
            t = t1;
        } else if (t1 < s1 && s1 < t2) {
            t = s1;
        } else if (t1 < s2 && s2 < t2) {
            t = s2;
        }
    }

    return t;
}

Vector* Cylindre::getNormal(Ray rayon) const{
    Vector* normal = 0;

    double t = this->getDistance(rayon);

    if (t == this->getDistanceToCylindre(rayon)) {
        Vector P = rayon.getOrigin() + t*rayon.getDirection();
        Vector D = this->getA() + ( (P - this->getA())*this->getDirection() )*this->getDirection();
        normal = new Vector(P-D);
        normal->Normalize();
    } else if (t == this->getDistanceToPlanA(rayon)) {
        normal = new Vector(this->getNormalA());
    } else if (t == this->getDistanceToPlanB(rayon)) {
        normal = new Vector(this->getNormalB());
    }

    return normal;
}

bool Cylindre::isInside(Vector point) const{
    bool is_inside = false;

    Vector D = this->getA() + ( (point - this->getA())*this->getDirection() )*this->getDirection();
    Vector normal = Vector(point-D);

    if (normal.norm() < this->getRadius()) {
        if ((this->getA()-point)*this->getNormalA() > 0 && (this->getB()-point)*this->getNormalB() > 0) {
            is_inside = true;
        }
    }

    return is_inside;
}

