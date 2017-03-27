#ifndef DEF_CUBE
#define DEF_CUBE

#include <cmath>
#include <random>

#include "Object.h"
#include "Vector.h"
#include "Material.h"
#include "Ray.h"
#include "Plan.h"

#include "Global.h"
#include "helping_functions.h"

class Cube : public Object {
public:
    /* Constructeur */
    Cube(Vector m_point, Vector m_dir1, Vector m_dir2, Vector m_dir3, Material* m_material);

    /* Destructeur */
    ~Cube();

    /* Masquage */
    std::vector<double> getIntersections(const Ray rayon) const;
    Vector getNormal(const Ray rayon) const;
    bool isInside(const Vector point) const;
    Ray getRandomRayToObject(Vector intersection) const;

protected:
    std::vector<Plan> planes;
    Vector point;
    Vector dir1;
    Vector dir2;
    Vector dir3;
    /* Plan plan1; */
    /* Plan plan1_bis; */
    /* Plan plan2; */
    /* Plan plan2_bis; */
    /* Plan plan3; */
    /* Plan plan3_bis; */
};

#endif

