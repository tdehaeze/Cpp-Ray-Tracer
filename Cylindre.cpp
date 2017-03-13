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




double Cylindre::getDistanceToPlanA(const Ray rayon) const{
    double t;

    if (rayon.getDirection()*this->getNormalA() != 0) {
        t = ((this->getA()-rayon.getOrigin())*this->getNormalA())/(rayon.getDirection()*this->getNormalA());
    } else {
        t = -INFINITY;
    }

    return t;
}

double Cylindre::getDistanceToPlanB(const Ray rayon) const{
    double t;

    if (rayon.getDirection()*this->getNormalB() != 0) {
        t = ((this->getB()-rayon.getOrigin())*this->getNormalB())/(rayon.getDirection()*this->getNormalB());
    } else {
        t = -INFINITY;
    }

    return t;
}

double Cylindre::getDistanceToCylindre(const Ray rayon) const{
    std::vector<double> t = this->getIntersectionsToCylindre(rayon);
    if (t.size() > 0) {
        return t[0];
    } else {
        return -INFINITY;
    }
}


std::vector<double> Cylindre::getIntersectionsToCylindre(Ray rayon) const{
    std::vector<double> t;

    Vector u = this->getDirection();
    Vector v = rayon.getDirection();
    Vector OA = rayon.getOrigin() - this->getA();
    double R = this->getRadius();

    double a = (v-(v*u)*u)*(v-(v*u)*u);
    double b = 2*(v-(v*u)*u)*(OA-(OA*u)*u);
    double c = (OA-(OA*u)*u)*(OA-(OA*u)*u)-R*R;

    double delta = b*b - 4*a*c;

    if (delta == 0 && -b/(2*a) >= 0) {
        t.push_back(-b/(2*a));
    } else if (delta > 0){
        t.push_back(-b+std::sqrt(delta));
        t.push_back(-b-std::sqrt(delta));
    }

    std::sort(t.begin(), t.end(), std::greater<int>());

    return t;
}


std::vector<double> Cylindre::getIntersections(const Ray rayon) const{
    std::vector<double> t;

    std::vector<double> t_cylindre = this->getIntersectionsToCylindre(rayon);

    /* If the ray crosses the infinit cylinder */
    if (t_cylindre.size() > 0) {
        if (rayon.getDirection() * this->getDirection() == 0) {
            /* the ray doesn't cross the 2 planes */
            t = t_cylindre;
        } else {
            /* the ray crosses both the planes and the cylinder */
            double s1 = this->getDistanceToPlanA(rayon);
            double s2 = this->getDistanceToPlanB(rayon);

            if (s1 > s2)
                std::swap(s1, s2);

            if (s1 <= t[0] && t[0] <= s2)
                t.push_back(t[0]);
            if (s1 <= t[1] && t[1] <= s2)
                t.push_back(t[1]);
            if (t[0] < s1 && s1 < t[1])
                t.push_back(s1);
            if (t[0] < s2 && s2 < t[1])
                t.push_back(s2);
        }
    } else if (rayon.getDirection() == this->getDirection()) {
        /* the ray has the same direction has the cylinder */
        /* double s1 = this->getDistanceToPlanA(rayon); */
        /* double s2 = this->getDistanceToPlanB(rayon); */
        /* TODO */

    }
    
    return t;
}

Vector* Cylindre::getNormal(const Ray rayon) const{
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

bool Cylindre::isInside(const Vector point) const{
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

