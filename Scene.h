#ifndef DEF_SCENE
#define DEF_SCENE

#include <cmath>
#include <algorithm>
#include <vector>
#include <random>
#include <iterator>

#include "Vector.h"
#include "Object.h"
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

    std::vector<Object*> getEmissiveObjects() const;
    Object* getRandomEmissiveObject() const;


protected:
    std::vector<Object*> objects;
    std::vector<Object*> emissive_objects;
};

#endif
