#ifndef DEF_SCENE
#define DEF_SCENE

#include <cmath>
#include <algorithm>
#include <vector>

#include "Vector.h"
#include "Object.h"
#include "Sphere.h"

#include "Ray.h"

class Scene {
public:
    /* constructeur */
    Scene();

    /* Destructeur */
    ~Scene();

    /* getter */
    std::vector<Object*> getObjects() const;

    void addSphere(Object* object);

    /* Sphere getSphere(Ray ray); */
    /* Sphere getCurrentSphere(Vector position); */

protected:
    std::vector<Object*> objects;
};

#endif
