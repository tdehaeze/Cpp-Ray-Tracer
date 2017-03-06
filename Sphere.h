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

    /* Getter */
    Vector getOrigin() const;
    double getRadius() const;

    /* Masquage */
    Material* getMaterial() const;
    double getDistance(const Ray rayon) const;
    Vector* getIntersect(const Ray rayon) const;
    Vector* getNormal(const Ray rayon) const;
    Ray* getReflectedRay(const Ray rayon) const;
    Ray* getRefractedRay(const Ray rayon) const;
    bool isInside(const Vector point) const;

protected:
    Vector origin;
    double radius;
    Material* material;
};

#endif
