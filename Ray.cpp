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


/* /1* get if the ray is crossing the sphere one time or two times or not at all *1/ */
/* double Ray::getDistanceToSphere(const Sphere sphere){ */
/*     double t; */

/*     Vector CO = origin - sphere.getOrigin(); */

/*     double a = 1; */
/*     double b = 2*direction*CO; */
/*     double c = CO.squaredNorm() - sphere.getRadius()*sphere.getRadius(); */

/*     double delta = b*b - 4*a*c; */

/*     double t1 = 0; */
/*     double t2 = 0; */

/*     if (delta < 0) { */
/*         t = -1; */
/*     } else if (delta == 0){ */
/*         t1 = -b/(2*a); */
/*         if (t1 > 0) { */
/*             t = t1; */
/*         } else { */
/*             t = -1; */
/*         } */
/*     } else { */
/*         t1 = (-b+sqrt(delta))/(2*a); */
/*         t2 = (-b-sqrt(delta))/(2*a); */
/*         if (t1 > 0 && t2 > 0) { */
/*             t = std::min(t1, t2); */
/*         } else if ((t1 < 0 && t2 > 0) || (t1 > 0 && t2 < 0)) { */
/*             t = std::max(t1, t2); */
/*         } else { */
/*             t = -1; */
/*         } */
/*     } */

/*     return t; */
/* } */

