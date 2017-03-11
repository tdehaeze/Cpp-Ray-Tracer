#include "Plan.h"

Plan::Plan(Vector m_origin, Vector m_direction, Material* m_material)
    : Object(m_material), origin(m_origin), direction(m_direction) {
        direction.Normalize();
    }

Plan::~Plan(){

}

Vector Plan::getOrigin() const{
    return origin;
}

Vector Plan::getDirection() const{
    return direction;
}

Vector Plan::getCenter() const{
    return origin;
}

Vector* Plan::getNormal(Ray rayon) const{
    Vector* normal = 0;
    if (rayon.getDirection()*direction != 0)
        normal = new Vector(direction);
    return normal;
}

double Plan::getDistance(Ray rayon) const{
    double t = -1;

    if (rayon.getDirection()*this->getDirection() != 0) {
        t = ((this->getOrigin()-rayon.getOrigin())*this->getDirection())/(rayon.getDirection()*this->getDirection());
        if (t < 0)
            t = -1;
    }

    return t;
}

/*
 * TODO: peut être faire en sorte de voir de quelle
 * côté on est par rapport à l'orientation de la normale
 * */
bool Plan::isInside(Vector point) const{
    return true;
}

