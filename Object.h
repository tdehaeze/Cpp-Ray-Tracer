#ifndef DEF_OBJECT
#define DEF_OBJECT

#include <iostream>
#include "Vector.h"
#include "Ray.h"
#include "Material.h"

class Object {
public:
    /* Constructeur */
    Object();

    /* Destructeur */
    virtual ~Object();

    virtual double getDistance(const Ray rayon) const = 0;
    virtual Material* getMaterial() const = 0;
    virtual Vector* getIntersect(const Ray rayon) const = 0;
    virtual Vector* getNormal(const Ray rayon) const = 0;
    virtual Vector* getReflectedRay(const Ray rayon) const = 0;
    virtual Vector* getRefractedRay(const Ray rayon) const = 0;

    virtual double getIntensity(const Ray rayon, const Light light) const;

    virtual bool isInside(const Vector point) const = 0;
};

#endif

