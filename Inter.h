#ifndef DEF_INTER
#define DEF_INTER

#include <iostream>
#include <cmath>

#include "Vector.h"
#include "Object.h"
#include "Ray.h"
#include "Material.h"
#include "Scene.h"

class Inter {
public:
    /* Constructeur */
    Inter(Scene scene, Ray m_ray, double m_n_before);

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


    Ray getReflectedRay(const Ray rayon) const;
    Ray getRefractedRay(const Ray rayon) const;
    Ray getRandomRay() const;

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


