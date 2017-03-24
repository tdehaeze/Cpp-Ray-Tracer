#include "Inter.h"

Inter::Inter(Object* m_object, Ray m_ray, double m_distance, double m_n_before)
    : object(m_object), distance(m_distance) {
        this->object = m_object;
        this->distance = m_distance;
        this->normal = Vector(0, 0, 0);
        this->point_intersect = Vector(0, 0, 0);
        this->point_before = Vector(0, 0, 0);
        this->point_after = Vector(0, 0, 0);
        this->n_before = m_n_before;
        if (m_object != 0) {
            this->point_intersect = m_ray.getOrigin() + m_distance*m_ray.getDirection();
            this->normal = *m_object->getNormal(m_ray);
            if (this->normal*m_ray.getDirection() > 0) { /* we are "inside" and going outside */
                this->point_before = this->point_intersect - 0.01*this->normal;
                this->point_after = this->point_intersect + 0.01*this->normal;
                this->n_after = 1.0;
            } else { /* we are outside and comming inside */
                this->point_before = this->point_intersect + 0.01*this->normal;
                this->point_after = this->point_intersect - 0.01*this->normal;
                this->n_after = m_object->getMaterial()->getIndice();
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

double Inter::getIndiceBefore() const{
    return this->n_before;
}

double Inter::getIndiceAfter() const{
    return this->n_after;
}


double Inter::getIntensity(Light light) const{
    double intensity;

    Vector l = Ray(this->getPointBeforeIntersect(), light).getDirection();
    Vector n = this->getNormal();

    double d = (this->getPointIntersect() - light.getOrigin()).norm();

    intensity = std::abs(l*n)*light.getIntensity()/(d*d);
    /* intensity = std::max(0.,l*n)*light.getIntensity()/(d*d); */

    /* if (DEBUG) std::cout << "l " << l << "\t---\t n " << n << std::endl; */

    return intensity;
}

Ray Inter::getReflectedRay(Ray rayon) const{
    Vector n = this->normal;
    Vector i = rayon.getDirection();

    Vector reflected_vector = i - 2*(i*n)*n;

    return Ray(this->point_before, reflected_vector);
}

Ray Inter::getRefractedRay(Ray rayon) const{
    Vector n = this->normal;
    Vector i = rayon.getDirection();

    double ind_frac = this->n_before/this->n_after;

    Vector refracted_direction = ind_frac*i - (-ind_frac*std::abs(n*i) + std::sqrt(1-ind_frac*ind_frac*(1 - (n*i)*(n*i))))*n;
    refracted_direction.Normalize();

    return Ray(this->point_before, refracted_direction);
}


Ray Inter::getRandomRay() const{
    Ray random_ray = Ray(this->point_before, help_fun::randomCos(this->normal));
    return random_ray;
}

