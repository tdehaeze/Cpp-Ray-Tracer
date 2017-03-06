#ifndef DEF_RAY
#define DEF_RAY

#include "Vector.h"
#include "Light.h"

class Ray {
public:
    /* constructor */
    Ray(Vector m_origin, Vector m_direction);
    Ray(Vector m_origin, Light light);
    /* Ray(int i, int j, int W, int H, int fov, Vector center); */

    /* getters */
    Vector getOrigin() const;
    Vector getDirection() const;

    /* double getDistanceToSphere(const Sphere sphere); */
    /* double getIntensity(Object* object, Light* light) const; */

protected:
    Vector origin;
    Vector direction;
};

#endif
