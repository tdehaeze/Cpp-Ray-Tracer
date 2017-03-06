#ifndef DEF_MATERIAL
#define DEF_MATERIAL

#include "Vector.h"

class Material {
public:
    /* Constructor */
    Material(Vector m_color = Vector(1., 1., 1.), double m_transparency = 0., double m_reflectivity = 0., double m_indice = 1.);

    /* Getters */
    Vector getColor() const;
    double getTransparency() const;
    double getReflectivity() const;
    double getIndice() const;

protected:
    Vector color;
    double transparency;
    double reflectivity;
    double indice;
};

#endif
