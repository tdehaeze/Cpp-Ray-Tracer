#ifndef DEF_CYLINDRE
#define DEF_CYLINDRE

#include <cmath>

#include "Object.h"
#include "Vector.h"
#include "Material.h"
#include "Ray.h"

#include "Global.h"
#include "helping_functions.h"

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

    /* Masquage */
    std::vector<double> getIntersections(const Ray rayon) const;
    Vector getNormal(const Ray rayon) const;
    bool isInside(const Vector point) const;
    Vector getRandomPoint() const;

protected:
    double getDistanceToPlanA(const Ray rayon) const;
    double getDistanceToPlanB(const Ray rayon) const;
    double getDistanceToCylindre(const Ray rayon) const;
    std::vector<double> getIntersectionsToCylindre(const Ray rayon) const;
    Vector a;
    Vector b;
    double radius;
};


#endif

