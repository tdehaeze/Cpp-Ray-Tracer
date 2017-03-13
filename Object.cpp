#include "Object.h"

Object::Object(Material* m_material)
    : material(m_material) {}

Object::~Object(){

}

Material* Object::getMaterial() const{
    return material;
}

double Object::getIntensity(Ray rayon, Light light) const{
    double intensity;

    Vector l = Ray(this->getPointBeforeIntersect(rayon), light).getDirection();
    Vector n = *this->getNormal(rayon);

    double d = (*this->getIntersect(rayon) - light.getOrigin()).norm();

    /* intensity = std::abs(l*n)*light.getIntensity()/(d*d); */
    intensity = std::max(0.,l*n)*light.getIntensity()/(d*d);

    /* std::cout << "l " << l << "\t---\t n " << n << std::endl; */

    return intensity;
}


Vector* Object::getIntersect(Ray rayon) const{
    double t = this->getDistance(rayon);
    if (t > 0) {
        /* std::cout << "t" << t << std::endl; */
        /* std::cout << "Origin of Ray : " << rayon.getOrigin() << std::endl; */
        /* std::cout << "Direction of Ray : " << rayon.getDirection() << std::endl; */
        Vector* intersect_point = new Vector(rayon.getOrigin() + t*rayon.getDirection());
        /* std::cout << "intersect_point" << *intersect_point << std::endl; */
        return intersect_point;
    } else {
        return 0;
    }
}

double Object::getDistance(const Ray rayon) const{
    std::vector<double> intersections = this->getIntersections(rayon);
    if (intersections.size() > 0) {
        return this->getFirstPositive(intersections);
    } else {
        return -1;
    }
}


Vector Object::getPointBeforeIntersect(Ray rayon) const{
    Vector point_before_intersect = *this->getIntersect(rayon);
    /* std::cout << "point_intersect: " << point_before_intersect << std::endl; */

    Vector intersect_normal = *this->getNormal(rayon);

    if (intersect_normal*rayon.getDirection() > 0) { /* we are "inside" and going outside */
        point_before_intersect -= 0.01*intersect_normal;
    } else { /* we are outside and comming inside */
        point_before_intersect += 0.01*intersect_normal;
    }

    /* std::cout << "point_before_intersect: " << point_before_intersect << std::endl; */

    return point_before_intersect;
}

Vector Object::getPointAfterIntersect(Ray rayon) const{
    Vector point_after_intersect = *this->getIntersect(rayon);
    Vector intersect_normal = *this->getNormal(rayon);

    if (intersect_normal*rayon.getDirection() > 0) { /* we are "inside" and going outside */
        point_after_intersect += 0.01*intersect_normal;
    } else { /* we are outside and comming inside */
        point_after_intersect -= 0.01*intersect_normal;
    }

    return point_after_intersect;
}

Ray Object::getReflectedRay(Ray rayon) const{
    Vector n = *this->getNormal(rayon);
    Vector i = rayon.getDirection();

    Vector reflected_vector = i - 2*(i*n)*n;

    return Ray(this->getPointBeforeIntersect(rayon), reflected_vector);
}

Ray Object::getRefractedRay(Ray rayon, double ind_before, double ind_after) const{
    Vector n = *this->getNormal(rayon);
    Vector i = rayon.getDirection();

    double ind_frac = ind_before/ind_after;

    Vector refracted_direction = ind_frac*i - (-ind_frac*std::abs(n*i) + std::sqrt(1-ind_frac*ind_frac*(1 - (n*i)*(n*i))))*n;
    refracted_direction.Normalize();

    return Ray(this->getPointAfterIntersect(rayon), refracted_direction);
}

double Object::getFirstPositive(const std::vector<double> t) const{
    for(const double &element : t) {
        if (element > 0) {
            return element;
        }
    }
    return -INFINITY;
}


