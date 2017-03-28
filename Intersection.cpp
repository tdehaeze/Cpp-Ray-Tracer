#include "Intersection.h"

Intersection::Intersection(Object* m_object1, Object* m_object2)
    : Object(m_object1->getMaterial()), object1(m_object1), object2(m_object2) {}

Intersection::~Intersection(){

}

Object* Intersection::getObject1() const{
    return object1;
}

Object* Intersection::getObject2() const{
    return object2;
}


std::vector<double> Intersection::getIntersections(const Ray rayon) const{
    std::vector<double> t1 = this->getObject1()->getIntersections(rayon);
    std::vector<double> t2 = this->getObject2()->getIntersections(rayon);

    std::vector<double> t_tot;

    for(auto const& t: t1) {
        Vector point = rayon.getOrigin() + t*rayon.getDirection();
        if (this->getObject2()->isInside(point))
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

Object* Intersection::getIntersectedObject(const Ray rayon) const{
    std::vector<double> intersections = this->getIntersections(rayon);
    double first_intersection = help_fun::getFirstPositive(intersections);

    if (first_intersection >= 0) {
        Vector point_before = rayon.getOrigin()+( first_intersection+0.00001 )*rayon.getDirection();
        Vector point_after = rayon.getOrigin()+( first_intersection-0.00001 )*rayon.getDirection();

        if (!this->getObject1()->isInside(point_before)) {
            return this->getObject1();
        } else if (!this->getObject2()->isInside(point_before)) {
            return this->getObject2();
        } else if (!this->getObject2()->isInside(point_after)) {
            return this->getObject2();
        } else {
            return this->getObject1();
        }
    } else {
        return 0;
    }
}

Vector Intersection::getNormal(const Ray rayon) const{
    Object* intersect_object = this->getIntersectedObject(rayon);
    return intersect_object->getNormal(rayon);
}

bool Intersection::isInside(const Vector point) const{
    return (this->getObject1()->isInside(point) && this->getObject2()->isInside(point));
}

Ray Intersection::getRandomRayToObject(Vector intersection) const{
    return this->getObject1()->getRandomRayToObject(intersection);
}

