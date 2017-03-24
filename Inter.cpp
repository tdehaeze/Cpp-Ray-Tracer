#include "Inter.h"

Inter::Inter(Object* m_object, Ray m_ray, double m_distance)
    : object(m_object), distance(m_distance) {
        this->object = m_object;
        this->distance = m_distance;
        this->normal = Vector(0, 0, 0);
        this->point_intersect = Vector(0, 0, 0);
        this->point_before = Vector(0, 0, 0);
        this->point_after = Vector(0, 0, 0);
        if (m_object != 0) {
            this->point_intersect = m_ray.getOrigin() + m_distance*m_ray.getDirection();
            this->normal = *m_object->getNormal(m_ray);
            if (this->normal*m_ray.getDirection() > 0) { /* we are "inside" and going outside */
                this->point_before = this->point_intersect - 0.01*this->normal;
                this->point_after = this->point_intersect + 0.01*this->normal;
            } else { /* we are outside and comming inside */
                this->point_before = this->point_intersect + 0.01*this->normal;
                this->point_after = this->point_intersect - 0.01*this->normal;
            }
        }
    }


Inter::~Inter(){

}

double Inter::getDistance() const{
    return this->distance;
}

Vector Inter::getNormal() const{
    return this->normal;
}

Vector Inter::getPointIntersect() const{
    return this->point_intersect;
}

Vector Inter::getPointAfterIntersect() const{
    return this->point_after;
}

Vector Inter::getPointBeforeIntersect() const{
    return this->point_before;
}

Object* Inter::getObject() const{
    return this->object;
}

