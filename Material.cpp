#include "Material.h"

Material::Material(Vector m_color, double m_transparency, double m_reflectivity)
    : color(m_color), transparency(m_transparency), reflectivity(m_reflectivity) {}

Vector Material::getColor() const{
    return color;
}

double Material::getTransparency() const{
    return transparency;
}

double Material::getReflectivity() const{
    return reflectivity;
}

