#ifndef DEF_OBJECT
#define DEF_OBJECT

#include "Vector.h"
#include "Ray.h"

class Object {
public:
    /* Constructeur */
    Object();

    /* Destructeur */
    virtual ~Object();

    virtual Vector* getIntersect(Ray rayon) const = 0;
    virtual bool isInside(Vector point) const = 0;
};

#endif

