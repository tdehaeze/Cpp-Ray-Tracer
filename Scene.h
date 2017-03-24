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

class Scene {
public:
    /* constructeur */
    Scene();

    /* Destructeur */
    ~Scene();

    /* getter */
    std::vector<Object*> getObjects() const;

    void addObject(Object* object);

protected:
    std::vector<Object*> objects;
};

#endif
