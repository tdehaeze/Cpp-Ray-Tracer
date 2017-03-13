#ifndef DEF_SCENE
#define DEF_SCENE

#include <cmath>
#include <algorithm>
#include <vector>

#include "Vector.h"
#include "Object.h"
#include "Sphere.h"
#include "Plan.h"

#include "Ray.h"

class Scene {
public:
    /* constructeur */
    Scene();

    /* Destructeur */
    ~Scene();

    /* getter */
    std::vector<Object*> getObjects() const;

    void addObject(Object* object);

    Object* getIntersectedObject(const Ray rayon) const;

    Vector* getIntersect(const Ray rayon) const;
    Vector* getNormal(const Ray rayon) const;
    Vector* getReflectedRay(const Ray rayon) const;
    Vector* getRefractedRay(const Ray rayon) const;

protected:
    std::vector<Object*> objects;
};

#endif
