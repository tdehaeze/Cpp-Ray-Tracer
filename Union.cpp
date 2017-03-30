#include "Union.h"

extern std::default_random_engine engine;
extern std::uniform_real_distribution <double> distrib;

Union::Union(Object* m_object1, Object* m_object2)
    : Object(m_object1->getMaterial()), object1(m_object1), object2(m_object2) {}

Union::~Union(){

}

Object* Union::getObject1() const{
    return object1;
}

Object* Union::getObject2() const{
    return object2;
}

Object* Union::getIntersectedObject(const Ray rayon) const{
    double t_1 = this->getObject1()->getDistance(rayon);
    double t_2 = this->getObject2()->getDistance(rayon);

    double t_min = 0;

    if (t_1*t_2 < 0) {
        t_min = std::max(t_1, t_2);
    } else {
        t_min = std::min(t_1, t_2);
    }

    if (t_min > 0) {
        if (t_min == t_1) {
            return this->getObject1();
        } else {
            return this->getObject2();
        }
    } else {
        return 0;
    }
}

std::vector<double> Union::getIntersections(const Ray rayon) const{
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
        if (!this->getObject1()->isInside(point))
            t_tot.push_back(t);
    }

    std::sort(t_tot.begin(), t_tot.end(), std::less<double>());

    return t_tot;
}

Vector Union::getNormal(const Ray rayon) const{
    Object* intersect_object = this->getIntersectedObject(rayon);
    return intersect_object->getNormal(rayon);
}

bool Union::isInside(const Vector point) const{
    return (this->getObject1()->isInside(point) || this->getObject2()->isInside(point));
}

Vector Union::getRandomPoint() const{
    if (distrib(engine) < 0.5) {
        return this->getObject1()->getRandomPoint();
    } else {
        return this->getObject2()->getRandomPoint();
    }
}

