#ifndef DEF_OBJECT
#define DEF_OBJECT

#include <iostream>

#include "Vector.h"
#include "Ray.h"
#include "Material.h"

#include "Global.h"
#include "helping_functions.h"

class Object {
public:
    /* Constructeur */
    Object(Material* m_material);

    /* Destructeur */
    virtual ~Object();

    /* Getter */
    virtual Material* getMaterial() const;

    /* Méthodes virtuelles pures */
    virtual std::vector<double> getIntersections(const Ray rayon) const = 0;
    virtual Vector getNormal(const Ray rayon) const = 0;
    virtual bool isInside(const Vector point) const = 0;
    virtual Vector getRandomPoint() const = 0;

    /* Autres méthodes */
    virtual Ray getRandomRayToObject(Vector intersection) const;
    virtual double getDistance(const Ray rayon) const;
    virtual Vector* getIntersect(const Ray rayon) const;

protected:
    Material* material;
};

#endif

