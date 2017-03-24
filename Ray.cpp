#include "Ray.h"

Ray::Ray(Vector m_origin, Vector m_direction)
    : origin(m_origin), direction(m_direction)
{
    direction.Normalize();
}

Ray::Ray(Vector m_origin, Light light)
    : origin(m_origin), direction(light.getOrigin()-m_origin)
{
    direction.Normalize();
}

/* Ray::Ray(int i, int j, int W, int H, int fov, Vector center) */
/*     : origin(center), direction(Vector(j-W/2+0.5, i-H/2+0.5, -H/(2*std::tan(2*M_PI*fov/2/360)))) { */
/*     direction.Normalize(); */
/* } */


Vector Ray::getOrigin() const {
    return origin;
}

Vector Ray::getDirection() const {
    return direction;
}

