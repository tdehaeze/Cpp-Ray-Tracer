#include "Material.h"

Material::Material(Vector m_color, Vector m_type, double m_indice, double m_emissivity)
    : color(m_color), type(m_type), indice(m_indice), emissivity(m_emissivity)
{
    this->color.Normalize();
    this->type = this->type/(this->type[0]+this->type[1]+this->type[2]);
}

Vector Material::getColor() const{
    return color;
}

double Material::getSpecularity() const{
    return this->type[0];
}

double Material::getTransparency() const{
    return this->type[1];
}

double Material::getReflectivity() const{
    return this->type[2];
}

double Material::getIndice() const{
    return indice;
}

double Material::getEmissivity() const{
    return emissivity;
}

