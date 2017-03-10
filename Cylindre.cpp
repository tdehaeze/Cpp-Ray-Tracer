#include "Cylindre.h"

Cylindre::Cylindre(Vector m_a, Vector m_b, double m_radius, Material* m_material)
    : Object(), a(m_a), b(m_b), radius(m_radius), material(m_material) {}

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

Material* Cylindre::getMaterial() const{
    return material;
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
        } else if (t1 < s1 && t2 > s1) {
            t = s1;
        } else if (t1 < s2 && t2 > s2) {
            t = s2;
        }
    }

    return t;
}

/* double Cylindre::getDistance(Ray rayon) const{ */
/*     double t = -1; */
    
    /* std::pair<double, double> t1t2 = this->getT1T2(rayon); */

    /* double t1 = t1t2.first; */
    /* double t2 = t1t2.second; */

    /* double s1 = this->getDistanceToPlanA(rayon); */
    /* double s2 = this->getDistanceToPlanB(rayon); */

    /* if (t1 > t2) */
    /*     std::swap(t1, t2); */
    /* if (s1 > s2) */
    /*     std::swap(s1, s2); */

    /* t = std::min(std::max(t1, s1), std::min(t2, s2)); */

    /* return t; */
/* } */


Vector* Cylindre::getIntersect(Ray rayon) const{
    double t = getDistance(rayon);
    if (t > 0) {
        Vector* intersect_point = new Vector(rayon.getOrigin() + t*rayon.getDirection());
        return intersect_point;
    } else {
        return 0;
    }
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

Vector Cylindre::getPointBeforeIntersect(Ray rayon) const{
    Vector point_before_intersect = *this->getIntersect(rayon);
    Vector intersect_normal = *this->getNormal(rayon);

    if (intersect_normal*rayon.getDirection() > 0) { /* we are "inside" and going outside */
        point_before_intersect -= 0.01*intersect_normal;
    } else { /* we are outside and comming inside */
        point_before_intersect += 0.01*intersect_normal;
    }

    return point_before_intersect;
}

Vector Cylindre::getPointAfterIntersect(Ray rayon) const{
    Vector point_after_intersect = *this->getIntersect(rayon);
    Vector intersect_normal = *this->getNormal(rayon);

    if (intersect_normal*rayon.getDirection() > 0) { /* we are "inside" and going outside */
        point_after_intersect += 0.01*intersect_normal;
    } else { /* we are outside and comming inside */
        point_after_intersect -= 0.01*intersect_normal;
    }

    return point_after_intersect;
}

Ray Cylindre::getReflectedRay(Ray rayon) const{
    Vector n = *this->getNormal(rayon);
    Vector i = rayon.getDirection();

    Vector reflected_vector = i - 2*(i*n)*n;

    return Ray(this->getPointBeforeIntersect(rayon), reflected_vector);
}

Ray Cylindre::getRefractedRay(Ray rayon, double ind_before, double ind_after) const{
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


