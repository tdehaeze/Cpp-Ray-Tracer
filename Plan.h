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
    std::vector<double> getIntersections(const Ray rayon) const;
    Vector getNormal(const Ray rayon) const;
    bool isInside(const Vector point) const;
    Ray getRandomRayToObject(Vector intersection) const;

protected:
    Vector origin;
    Vector direction;
};

#endif
