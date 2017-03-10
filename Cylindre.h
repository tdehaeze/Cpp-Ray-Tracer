#ifndef DEF_CYLINDRE
#define DEF_CYLINDRE

#include <cmath>

#include "Object.h"
#include "Vector.h"
#include "Material.h"
#include "Ray.h"

class Cylindre : public Object {
public:
    /* Constructeur */
    Cylindre(Vector m_a = Vector(0, 0, 0), Vector m_b = Vector(0, 0, 0), double m_radius = 0, Material* m_material = NULL);

    /* Destructeur */
    ~Cylindre();

    /* Getter */
    Vector getA() const;
    Vector getB() const;
    double getRadius() const;

    Vector getDirection() const;
    Vector getNormalA() const;
    Vector getNormalB() const;

    double getDistanceToPlanA(const Ray rayon) const;
    double getDistanceToPlanB(const Ray rayon) const;
    double getDistanceToCylindre(const Ray rayon) const;
    std::pair<double, double> getT1T2(const Ray rayon) const;

    /* Masquage */
    Material* getMaterial() const;
    Vector getCenter() const;
    double getDistance(const Ray rayon) const;
    Vector* getIntersect(const Ray rayon) const;
    Vector* getNormal(const Ray rayon) const;
    Ray getReflectedRay(const Ray rayon) const;
    Ray getRefractedRay(const Ray rayon, double ind_before, double ind_after) const;
    Vector getPointBeforeIntersect(const Ray rayon) const;
    Vector getPointAfterIntersect(const Ray rayon) const;
    bool isInside(const Vector point) const;

protected:
    Vector a;
    Vector b;
    double radius;
    Material* material;
};

#endif

