#ifndef DEF_RAY
#define DEF_RAY

#include "Vector.h"

class Ray {
public:
    /* constructor */
    Ray(Vector m_origin, Vector m_direction);

    /* getters */
    Vector getOrigin() const;
    Vector getDirection() const;

    /* double getDistanceToSphere(const Sphere sphere); */
    /* double getIntensity(const Sphere sphere, double t, Light light); */

protected:
    Vector origin;
    Vector direction;
};

#endif
