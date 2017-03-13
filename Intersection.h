#ifndef DEF_INTERSECTION
#define DEF_INTERSECTION

#include <cmath>

#include "Object.h"
#include "Vector.h"
#include "Material.h"
#include "Ray.h"
#include "global.h"
#include "helping_functions.h"

class Intersection : public Object {
public:
    /* Constructeur */
    Intersection(Object* m_object1 = 0, Object* m_object2 = 0);

    /* Destructeur */
    ~Intersection();

    /* Getter */
    Object* getObject1() const;
    Object* getObject2() const;

    /* Masquage */
    std::vector<double> getIntersections(const Ray rayon) const;
    Vector* getNormal(const Ray rayon) const;
    bool isInside(const Vector point) const;

protected:
    Object* getIntersectedObject(const Ray rayon) const;

    Object* object1;
    Object* object2;
};

#endif



