#include "Object.h"

Object::Object(){

}

Object::~Object(){

}

double Object::getIntensity(Ray rayon, Light light) const{
    double intensity;

    Vector l = Ray(*this->getIntersect(rayon), light).getDirection();
    Vector n = *this->getNormal(rayon);

    double d = (*this->getIntersect(rayon) - light.getOrigin()).norm();

    intensity = std::abs(l*n)*light.getIntensity()/(d*d);

    return intensity;
}

