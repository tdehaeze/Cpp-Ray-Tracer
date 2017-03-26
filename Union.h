#ifndef DEF_UNION
#define DEF_UNION

#include <cmath>

#include "Object.h"
#include "Vector.h"
#include "Material.h"
#include "Ray.h"

class Union : public Object {
public:
    /* Constructeur */
    Union(Object* m_object1 = 0, Object* m_object2 = 0);

    /* Destructeur */
    ~Union();

    /* Getter */
    Object* getObject1() const;
    Object* getObject2() const;

    /* Masquage */
    std::vector<double> getIntersections(const Ray rayon) const;
    Vector* getNormal(const Ray rayon) const;
    bool isInside(const Vector point) const;
    Ray getRandomRayToObject(Vector intersection) const;

protected:
    Object* getIntersectedObject(const Ray rayon) const;

    Object* object1;
    Object* object2;
};

#endif


