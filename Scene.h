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
#include "Global.h"
#include "Inter.h"

class Scene {
public:
    /* constructeur */
    Scene();

    /* Destructeur */
    ~Scene();

    /* getter */
    std::vector<Object*> getObjects() const;

    void addObject(Object* object);

    Inter* getInter(const Ray rayon, double indice) const;

    /* Vector* getIntersect(const Ray rayon) const; */
    /* Vector* getNormal(const Ray rayon) const; */
    /* Vector* getReflectedRay(const Ray rayon) const; */
    /* Vector* getRefractedRay(const Ray rayon) const; */

protected:
    std::vector<Object*> objects;
};

#endif
