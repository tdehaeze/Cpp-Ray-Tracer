#ifndef DEF_OBJECT
#define DEF_OBJECT

#include <iostream>
#include "Vector.h"
#include "Ray.h"
#include "Material.h"
#include "global.h"
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
    virtual Vector* getNormal(const Ray rayon) const = 0;
    virtual bool isInside(const Vector point) const = 0;

    /* Autres méthodes */
    virtual double getDistance(const Ray rayon) const;
    virtual Vector* getIntersect(const Ray rayon) const;
    virtual Ray getReflectedRay(const Ray rayon) const;
    virtual Ray getRefractedRay(const Ray rayon, double ind_before, double ind_after) const;
    virtual Vector getPointBeforeIntersect(const Ray rayon) const;
    virtual Vector getPointAfterIntersect(const Ray rayon) const;
    virtual double getIntensity(const Ray rayon, const Light light) const;

protected:
    Material* material;
};

#endif

