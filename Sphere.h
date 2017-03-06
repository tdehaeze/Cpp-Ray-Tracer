#ifndef DEF_SPHERE
#define DEF_SPHERE

#include <cmath>

#include "Object.h"
#include "Vector.h"
#include "Material.h"
#include "Ray.h"

class Sphere : public Object {
public:
    /* Constructeur */
    Sphere(Vector m_origin = Vector(0, 0, 0), double m_radius = 0., Material* m_material = NULL);

    /* Destructeur */
    ~Sphere();

    /* getter */
    Vector getOrigin() const;
    double getRadius() const;
    Material* getMaterial() const;

    /* masquage */
    Vector* getIntersect(Ray rayon) const;
    bool isInside(Vector point) const;

protected:
    Vector origin;
    double radius;
    Material* material;
};

#endif
