#include "Plan.h"

Plan::Plan(Vector m_origin, Vector m_direction, Material* m_material)
    : Object(m_material), origin(m_origin), direction(m_direction)
{
    this->direction.Normalize();
}

Plan::~Plan(){

}

Vector Plan::getOrigin() const{
    return origin;
}

Vector Plan::getDirection() const{
    return direction;
}

/* TODO */
Vector Plan::getNormal(Ray rayon) const{
    return direction;
    /* Vector normal = Vector(0, 0, 0); */
    /* if (rayon.getDirection()*this->direction != 0) */
    /*     normal = this->direction; */
    /* return normal; */
}

bool Plan::isInside(Vector point) const{
    return this->getDirection()*(point-this->getOrigin()) < 0;
}

/* TODO Mieux gérer le cas lorsqu'on est parrallèle */
std::vector<double> Plan::getIntersections(const Ray rayon) const{
    std::vector<double> intersections;

    if (rayon.getDirection()*this->getDirection() != 0)
        intersections.push_back(((this->getOrigin()-rayon.getOrigin())*this->getDirection())/(rayon.getDirection()*this->getDirection()));

    return intersections;
}

Ray Plan::getRandomRayToObject(Vector intersection) const{
    std::cout << "getRandomRayToObject inside Plan NOT IMPLEMENTED" << std::endl;
    return Ray(intersection, this->getOrigin()-intersection);
}

