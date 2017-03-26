#include "Light.h"

Light::Light(Vector m_origin, double m_intensity, double m_radius)
    : origin(m_origin), intensity(m_intensity), radius(m_radius) {}

Vector Light::getOrigin() const{
    return origin;
}

double Light::getIntensity() const{
    return intensity;
}

double Light::getRadius() const{
    return radius;
}

