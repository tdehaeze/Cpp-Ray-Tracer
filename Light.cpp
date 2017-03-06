#include "Light.h"

Light::Light(Vector m_origin, double m_intensity)
    : origin(m_origin), intensity(m_intensity) {}

Vector Light::getOrigin() const{
    return origin;
}

double Light::getIntensity() const{
    return intensity;
}

