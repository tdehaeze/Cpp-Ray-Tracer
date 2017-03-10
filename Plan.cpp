#include "Plan.h"

Plan::Plan(Vector m_origin, Vector m_direction, Material* m_material)
    : Object(), origin(m_origin), direction(m_direction), material(m_material) {}

Plan::~Plan(){

}

Vector Plan::getOrigin() const{
    return origin;
}

Vector Plan::getDirection() const{
    return direction;
}

Material* Plan::getMaterial() const{
    return material;
}

Vector Plan::getCenter() const{
    return origin;
}

Vector* Plan::getIntersect(Ray rayon) const{
    double t = getDistance(rayon);
    if (t > 0) {
        Vector* intersect_point = new Vector(rayon.getOrigin() + t*rayon.getDirection());
        return intersect_point;
    } else {
        return 0;
    }
}

Vector* Plan::getNormal(Ray rayon) const{
    Vector* normal = 0;
    /* if (rayon.getDirection()*direction != 0) */
        *normal = direction;
    return normal;
}

double Plan::getDistance(Ray rayon) const{
    double t = -1;

    /* if (rayon.getDirection()*this->getDirection() != 0) { */
        t = ((this->getOrigin()-rayon.getOrigin())*direction)/(rayon.getDirection()*this->getDirection());
        if (t < 0)
            t = -1;
    /* } */

    return t;
}

/*
 * TODO: peut être faire en sorte de voir de quelle
 * côté on est par rapport à l'orientation de la normale
 * */
bool Plan::isInside(Vector point) const{
    return true;
}

Vector Plan::getPointBeforeIntersect(Ray rayon) const{
    Vector point_before_intersect = *this->getIntersect(rayon);
    Vector intersect_normal = *this->getNormal(rayon);

    if (intersect_normal*rayon.getDirection() > 0) { /* we are "inside" and going outside */
        point_before_intersect -= 0.01*intersect_normal;
    } else { /* we are outside and comming inside */
        point_before_intersect += 0.01*intersect_normal;
    }

    return point_before_intersect;
}

Vector Plan::getPointAfterIntersect(Ray rayon) const{
    Vector point_after_intersect = *this->getIntersect(rayon);
    Vector intersect_normal = *this->getNormal(rayon);

    if (intersect_normal*rayon.getDirection() > 0) { /* we are "inside" and going outside */
        point_after_intersect += 0.01*intersect_normal;
    } else { /* we are outside and comming inside */
        point_after_intersect -= 0.01*intersect_normal;
    }

    return point_after_intersect;
}

Ray Plan::getReflectedRay(Ray rayon) const{
    Vector n = *this->getNormal(rayon);
    Vector i = rayon.getDirection();

    Vector reflected_vector = i - 2*(i*n)*n;

    return Ray(this->getPointBeforeIntersect(rayon), reflected_vector);
}

Ray Plan::getRefractedRay(Ray rayon, double ind_before, double ind_after) const{
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

