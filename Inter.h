#ifndef DEF_INTER
#define DEF_INTER

#include <iostream>
#include <cmath>

#include "Vector.h"
#include "Object.h"
#include "Ray.h"
#include "Material.h"

class Inter {
public:
    /* Constructeur */
    Inter(Object* m_object, Ray m_ray, double m_distance, double m_n_before);

    /* Destructeur */
    virtual ~Inter();

    /* Getter */
    Object* getObject() const;
    double getDistance() const;
    Vector getNormal() const;
    Vector getPointIntersect() const;
    Vector getPointBeforeIntersect() const;
    Vector getPointAfterIntersect() const;
    double getIndiceBefore() const;
    double getIndiceAfter() const;


    Ray getRandomRay() const;
    Ray getReflectedRay(const Ray rayon) const;
    Ray getRefractedRay(const Ray rayon) const;
    double getIntensity(const Light light) const;

protected:
    Object* object;
    double distance;
    Vector normal;
    Vector point_intersect;
    Vector point_before;
    Vector point_after;
    double n_before;
    double n_after;
};

#endif


