#ifndef DEF_PLAN
#define DEF_PLAN

#include <cmath>

#include "Object.h"
#include "Vector.h"
#include "Material.h"
#include "Ray.h"

class Plan : public Object {
public:
    /* Constructeur */
    Plan(Vector m_origin = Vector(0, 0, 0), Vector m_direction = Vector(0, 0, 0), Material* m_material = NULL);

    /* Destructeur */
    ~Plan();

    /* Getter */
    Vector getOrigin() const;
    Vector getDirection() const;

    /* Masquage */
    Material* getMaterial() const;
    Vector getCenter() const;
    double getDistance(const Ray rayon) const;
    Vector* getIntersect(const Ray rayon) const;
    Vector* getNormal(const Ray rayon) const;
    Ray getReflectedRay(const Ray rayon) const;
    Ray getRefractedRay(const Ray rayon, double ind_before, double ind_after) const;
    Vector getPointBeforeIntersect(const Ray rayon) const;
    Vector getPointAfterIntersect(const Ray rayon) const;
    bool isInside(const Vector point) const;

protected:
    Vector origin;
    Vector direction;
    Material* material;
};

#endif
