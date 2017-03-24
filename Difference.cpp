#include "Difference.h"

Difference::Difference(Object* m_object1, Object* m_object2)
    : Object(m_object1->getMaterial()), object1(m_object1), object2(m_object2) {}

Difference::~Difference(){

}

Object* Difference::getObject1() const{
    return object1;
}

Object* Difference::getObject2() const{
    return object2;
}


std::vector<double> Difference::getIntersections(const Ray rayon) const{
    std::vector<double> t1 = this->getObject1()->getIntersections(rayon);
    std::vector<double> t2 = this->getObject2()->getIntersections(rayon);

    std::vector<double> t_tot;

    for(auto const& t: t1) {
        Vector point = rayon.getOrigin() + t*rayon.getDirection();
        if (!this->getObject2()->isInside(point))
            t_tot.push_back(t);
    }

    for(auto const& t: t2) {
        Vector point = rayon.getOrigin() + t*rayon.getDirection();
        if (this->getObject1()->isInside(point))
            t_tot.push_back(t);
    }

    std::sort(t_tot.begin(), t_tot.end(), std::less<double>());

    return t_tot;
}

Object* Difference::getIntersectedObject(const Ray rayon) const{
    std::vector<double> intersections = this->getIntersections(rayon);
    double first_intersection = help_fun::getFirstPositive(intersections);

    if (first_intersection >= 0) {
        return this->getObject1();
    } else {
        return 0;
    }
}

Vector* Difference::getNormal(const Ray rayon) const{
    Object* intersect_object = this->getIntersectedObject(rayon);
    return intersect_object->getNormal(rayon);
}

bool Difference::isInside(const Vector point) const{
    return (this->getObject1()->isInside(point) && !this->getObject2()->isInside(point));
}

