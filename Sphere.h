#ifndef DEF_SPHERE
#define DEF_SPHERE

#include <cmath>
#include <random>

#include "Object.h"
#include "Vector.h"
#include "Material.h"
#include "Ray.h"

#include "Global.h"
#include "helping_functions.h"

class Sphere : public Object {
public:
    /* Constructeur */
    Sphere(Vector m_origin = Vector(0, 0, 0), double m_radius = 0., Material* m_material = NULL);

    /* Destructeur */
    ~Sphere();

    /* Getter */
    Vector getOrigin() const;
    double getRadius() const;

    /* Masquage */
    std::vector<double> getIntersections(const Ray rayon) const;
    Vector getNormal(const Ray rayon) const;
    bool isInside(const Vector point) const;
    Vector getRandomPoint() const;

protected:
    Vector origin;
    double radius;
};

#endif

