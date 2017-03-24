#include "Object.h"

extern std::default_random_engine engine;
extern std::uniform_real_distribution <double> distrib;

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

    /* if (DEBUG) std::cout << "l " << l << "\t---\t n " << n << std::endl; */

    return intensity;
}


Vector* Object::getIntersect(Ray rayon) const{
    double t = this->getDistance(rayon);
    if (t > 0) {
        /* if (DEBUG) std::cout << "t" << t << std::endl; */
        /* if (DEBUG) std::cout << "Origin of Ray : " << rayon.getOrigin() << std::endl; */
        /* if (DEBUG) std::cout << "Direction of Ray : " << rayon.getDirection() << std::endl; */
        Vector* intersect_point = new Vector(rayon.getOrigin() + t*rayon.getDirection());
        /* if (DEBUG) std::cout << "intersect_point" << *intersect_point << std::endl; */
        return intersect_point;
    } else {
        return 0;
    }
}

double Object::getDistance(const Ray rayon) const{
    std::vector<double> intersections = this->getIntersections(rayon);
    if (DEBUG) std::cout << "après get intersections" << std::endl;
    if (intersections.size() > 0) {
        return getFirstPositive(intersections);
    } else {
        return -1;
    }
}


Vector Object::getPointBeforeIntersect(Ray rayon) const{
    if (DEBUG) std::cout << "lapin 0" << std::endl;
    Vector point_before_intersect = *this->getIntersect(rayon);
    if (DEBUG) std::cout << "lapin 1" << std::endl;
    Vector intersect_normal = *this->getNormal(rayon);
    if (DEBUG) std::cout << "lapin 2" << std::endl;
    
    if (intersect_normal*rayon.getDirection() > 0) { /* we are "inside" and going outside */
        point_before_intersect -= 0.01*intersect_normal;
    } else { /* we are outside and comming inside */
        point_before_intersect += 0.01*intersect_normal;
    }

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

Vector Object::randomCos(const Vector normal) const{
    double u = distrib(engine);
    double v = distrib(engine);

    double x = cos(2*M_PI*u)*sqrt(1-v);
    double y = sin(2*M_PI*u)*sqrt(1-v);
    double z = sqrt(v);

    Vector r1(distrib(engine), distrib(engine), distrib(engine));
    r1.Normalize();

    Vector tangent1 = normal^r1;
    Vector tangent2 = normal^tangent1;

    return x*tangent1 + y*tangent2 + z*normal;
}

Ray Object::getRandomRay(const Ray rayon) const{
    Vector normal = *this->getNormal(rayon);
    Ray random_ray = Ray(this->getPointBeforeIntersect(rayon), this->randomCos(normal));
    return random_ray;
}

