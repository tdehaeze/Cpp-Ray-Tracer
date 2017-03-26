#ifndef DEF_LIGHT
#define DEF_LIGHT

#include <cmath>
#include "Vector.h"

class Light {
public:
    /* constructor */
    Light(Vector m_origin, double m_intensity, double m_radius);

    /* getter */
    Vector getOrigin() const;
    double getIntensity() const;
    double getRadius() const;

protected:
    Vector origin;
    double intensity;
    double radius;
};

#endif
