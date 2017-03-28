#include "Inter.h"

Inter::Inter(Scene scene, Ray m_ray, double m_n_before)
    : n_before(m_n_before)
{
    Object* closest_object = 0;
    double t_min = -1;

    for(auto const& object: scene.getObjects()) {
        double t = object->getDistance(m_ray);
        if (t > 0 && ( t < t_min || t_min < 0 )) {
            closest_object = object;
            t_min = t;
        }
    }

    this->object = closest_object;
    this->distance = t_min;
    this->normal = Vector(0, 0, 0);
    this->point_intersect = Vector(0, 0, 0);
    this->point_before = Vector(0, 0, 0);
    this->point_after = Vector(0, 0, 0);
    this->n_before = m_n_before;

    if (closest_object != 0) {
        this->point_intersect = m_ray.getOrigin() + t_min*m_ray.getDirection();
        this->normal = closest_object->getNormal(m_ray);
        if (this->normal*m_ray.getDirection() > 0) { /* we are "inside" and going outside */
            this->point_before = this->point_intersect + 0.00001*m_ray.getDirection();
            /* this->point_after = this->point_intersect - 0.00001*m_ray.getDirection(); */
            /* this->point_before = this->point_intersect - 0.00001*this->normal; */
            this->point_after = this->point_intersect + 0.00001*this->normal;
            /* TODO : voir les indices */
            this->n_after = 1.0;
        } else { /* we are outside and comming inside */
            this->point_before = this->point_intersect - 0.00001*m_ray.getDirection();
            /* this->point_after = this->point_intersect + 0.00001*m_ray.getDirection(); */
            /* this->point_before = this->point_intersect + 0.00001*this->normal; */
            this->point_after = this->point_intersect - 0.00001*this->normal;
            this->n_after = closest_object->getMaterial()->getIndice();
        }

        if (this->object->isInside(this->point_before)) {
            std::cout << "point before should not be inside" << std::endl;
        } else if (!this->object->isInside(this->point_after)) {
            std::cout << "point after should be inside" << std::endl;
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


double Inter::getIntensity(Ray ray_to_light) const{
    double intensity;

    Vector l = ray_to_light.getDirection();
    Vector n = this->getNormal();

    /* double d = (this->getPointIntersect() - light.getOrigin()).norm(); */
    /* double d = this->getDistance(); */

    /* intensity = std::abs(l*n)*light.getIntensity()/(d*d); */
    /* intensity = std::max(0.,l*n)*light.getIntensity()/(d*d); */
    intensity = std::max(0.,l*n);

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

    return Ray(this->point_after, refracted_direction);
}

Ray Inter::getRandomRay() const{
    return Ray(this->getPointBeforeIntersect(), help_fun::randomCos(this->getNormal()));
}

