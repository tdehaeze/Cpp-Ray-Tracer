#ifndef DEF_MATERIAL
#define DEF_MATERIAL

#include "Vector.h"

class Material {
public:
    /* Constructor */
    Material(Vector m_color = Vector(1., 1., 1.), Vector m_type = Vector (1., 0., 0.), double m_indice = 1., double m_emissivity = 0.);

    /* Getters */
    Vector getColor() const;
    double getSpecularity() const;
    double getTransparency() const;
    double getReflectivity() const;
    double getIndice() const;
    double getEmissivity() const;

protected:
    Vector color;
    Vector type;
    double indice;
    double emissivity;
};

#endif
