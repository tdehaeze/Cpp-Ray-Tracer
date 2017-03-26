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

    Vector normal_a = this->getNormalA();

    if (!help_fun::double_equals(rayon.getDirection()*normal_a, 0)) {
        t = ((this->getA()-rayon.getOrigin())*normal_a)/(rayon.getDirection()*normal_a);
    } else {
        t = -1;
    }

    return t;
}

double Cylindre::getDistanceToPlanB(const Ray rayon) const{
    double t;

    Vector normal_b = this->getNormalB();

    if (!help_fun::double_equals(rayon.getDirection()*normal_b, 0)) {
        t = ((this->getB()-rayon.getOrigin())*normal_b)/(rayon.getDirection()*normal_b);
    } else {
        t = -1;
    }

    return t;
}

double Cylindre::getDistanceToCylindre(const Ray rayon) const{
    double first_positive = help_fun::getFirstPositive(this->getIntersectionsToCylindre(rayon));
    if (first_positive > 0) {
        return first_positive;
    } else {
        return -1;
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

    if (delta == 0) {
        t.push_back(-b/(2*a));
    } else if (delta > 0){
        t.push_back((-b+std::sqrt(delta))/(2*a));
        t.push_back((-b-std::sqrt(delta))/(2*a));
    }

    std::sort(t.begin(), t.end(), std::less<double>());

    if (DEBUG) {
        if (t.size() == 0) {
            std::cout << "T : size 0" << std::endl;
        } else if (t.size() == 1) {
            std::cout << "T0 = " << t[0] << std::endl;
        } else if (t.size() == 2) {
            std::cout << "T0 = " << t[0] << "T1 = " << t[1] << std::endl;
        }
    }

    return t;
}


std::vector<double> Cylindre::getIntersections(const Ray rayon) const{
    std::vector<double> t;

    std::vector<double> t_cylindre = this->getIntersectionsToCylindre(rayon);

    /* If the ray crosses the infinit cylinder */
    if (t_cylindre.size() > 1) {
        if (help_fun::double_equals(rayon.getDirection()*this->getDirection(), 0)) {
            /* the ray doesn't cross the 2 planes */
            if (DEBUG) std::cout << "ray doesn't cross planes" << std::endl;
            t = t_cylindre;
        } else {
            /* the ray crosses both the planes and the cylinder */
            double s1 = this->getDistanceToPlanA(rayon);
            double s2 = this->getDistanceToPlanB(rayon);
            if (DEBUG) std::cout << "s1 : " << s1 << std::endl;
            if (DEBUG) std::cout << "s2 : " << s2 << std::endl;

            if (s1 > s2)
                std::swap(s1, s2);

            if (DEBUG) std::cout << "s1 : " << s1 << std::endl;
            if (DEBUG) std::cout << "s2 : " << s2 << std::endl;

            if (DEBUG) std::cout << "t_cylindre[0] : " << t_cylindre[0] << std::endl;
            if (DEBUG) std::cout << "t_cylindre1] : " << t_cylindre[1] << std::endl;

            if (s1 <= t_cylindre[0] && t_cylindre[0] <= s2)
                t.push_back(t_cylindre[0]);
            if (s1 <= t_cylindre[1] && t_cylindre[1] <= s2)
                t.push_back(t_cylindre[1]);
            if (t_cylindre[0] < s1 && s1 < t_cylindre[1])
                t.push_back(s1);
            if (t_cylindre[0] < s2 && s2 < t_cylindre[1])
                t.push_back(s2);

            if (DEBUG) std::cout << "crosses the sphere" << std::endl;
        }
    } else if (help_fun::double_equals((rayon.getDirection()^this->getDirection()).norm(), 0)) {
        /* the ray has the same direction has the cylinder */
        /* double s1 = this->getDistanceToPlanA(rayon); */
        /* double s2 = this->getDistanceToPlanB(rayon); */
        /* TODO */
        if (DEBUG) std::cout << "cas pas encore pris en compte" << std::endl;

    }

    std::sort(t.begin(), t.end(), std::less<double>());

    return t;
}

Vector* Cylindre::getNormal(const Ray rayon) const{
    Vector* normal = 0;

    double t = this->getDistance(rayon);

    if (help_fun::double_equals(t, this->getDistanceToCylindre(rayon))) {
        /* std::cout << "cylindre" << std::endl; */
        Vector P = rayon.getOrigin() + t*rayon.getDirection();
        Vector D = this->getA() + ( (P - this->getA())*this->getDirection() )*this->getDirection();
        normal = new Vector(P-D);
        normal->Normalize();
    } else if (help_fun::double_equals(t, this->getDistanceToPlanA(rayon))) {
        /* std::cout << "planA" << std::endl; */
        normal = new Vector(this->getNormalA());
    } else if (help_fun::double_equals(t, this->getDistanceToPlanB(rayon))) {
        /* std::cout << "planB" << std::endl; */
        normal = new Vector(this->getNormalB());
    } else {
        std::cout << "SHOULD NEVER GO HERE" << std::endl;
        Vector P = rayon.getOrigin() + t*rayon.getDirection();
        Vector D = this->getA() + ( (P - this->getA())*this->getDirection() )*this->getDirection();
        normal = new Vector(P-D);
        normal->Normalize();
    }
    /* std::cout << "after" << std::endl; */
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

Ray Cylindre::getRandomRayToObject(Vector intersection) const{
    return Ray(intersection, (this->getA() + this->getB())/2 - intersection);
}


