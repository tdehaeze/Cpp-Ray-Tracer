#ifndef DEF_INTER
#define DEF_INTER

#include <iostream>

#include "Vector.h"
#include "Object.h"
#include "Ray.h"
#include "Material.h"

class Inter {
public:
    /* Constructeur */
    Inter(Object* m_object, Ray m_ray, double m_distance);

    /* Destructeur */
    virtual ~Inter();

    /* Getter */
    Object* getObject() const;
    double getDistance() const;
    Vector getNormal() const;
    Vector getPointIntersect() const;
    Vector getPointBeforeIntersect() const;
    Vector getPointAfterIntersect() const;

protected:
    Object* object;
    double distance;
    Vector normal;
    Vector point_intersect;
    Vector point_before;
    Vector point_after;
};

#endif


