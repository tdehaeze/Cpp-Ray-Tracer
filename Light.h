#ifndef DEF_LIGHT
#define DEF_LIGHT

#include <cmath>
#include "Vector.h"

class Light {
public:
    /* constructor */
    Light(Vector m_origin, double m_intensity);

    /* getter */
    Vector getOrigin() const;
    double getIntensity() const;

protected:
    Vector origin;
    double intensity;
};

#endif
