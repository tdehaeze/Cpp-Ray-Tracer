#include "Cube.h"

extern std::default_random_engine engine;
extern std::uniform_real_distribution <double> distrib;

Cube::Cube(Vector m_point, Vector m_dir1, Vector m_dir2, Vector m_dir3, Material* m_material) :
    Object(m_material), point(m_point), dir1(m_dir1), dir2(m_dir2), dir3(m_dir3)
{
    Vector m_point_bis = m_point+m_dir1+m_dir2+m_dir3;

    planes = {
        Plan(m_point,     -m_dir1, m_material),
        Plan(m_point_bis, m_dir1,  m_material),
        Plan(m_point,     -m_dir2, m_material),
        Plan(m_point_bis, m_dir2,  m_material),
        Plan(m_point,     -m_dir3, m_material),
        Plan(m_point_bis, m_dir3,  m_material)
    };

    /* planes.push_back(Plan(m_point+m_dir3, m_dir3,  m_material)); */
    /* planes.push_back(Plan(m_point,        -m_dir3, m_material)); */
    /* planes.push_back(Plan(m_point+m_dir2, m_dir2,  m_material)); */
    /* planes.push_back(Plan(m_point,        -m_dir2, m_material)); */
    /* planes.push_back(Plan(m_point+m_dir1, m_dir1,  m_material)); */
    /* planes.push_back(Plan(m_point,        -m_dir1, m_material)); */

    /* this->plan1     = Plan(point,      -dir1, m_material); */
    /* this->plan1_bis = Plan(point+dir1, dir1,  m_material); */
    /* this->plan2     = Plan(point,      -dir2, m_material); */
    /* this->plan2_bis = Plan(point+dir2, dir2,  m_material); */
    /* this->plan3     = Plan(point,      -dir3, m_material); */
    /* this->plan3_bis = Plan(point+dir3, dir3,  m_material); */
}

Cube::~Cube(){

}

std::vector<double> Cube::getIntersections(const Ray rayon) const{
    std::vector<double> intersections;

    double t_1     = this->planes[0].getIntersections(rayon)[0];
    double t_1_bis = this->planes[1].getIntersections(rayon)[0];
    double t_2     = this->planes[2].getIntersections(rayon)[0];
    double t_2_bis = this->planes[3].getIntersections(rayon)[0];
    double t_3     = this->planes[4].getIntersections(rayon)[0];
    double t_3_bis = this->planes[5].getIntersections(rayon)[0];

    /* std::cout << "t_1 : " << t_1 << std::endl; */
    /* std::cout << "t_1_bis : " << t_1_bis << std::endl; */
    /* std::cout << "t_2 : " << t_2 << std::endl; */
    /* std::cout << "t_2_bis : " << t_2_bis << std::endl; */
    /* std::cout << "t_3 : " << t_3 << std::endl; */
    /* std::cout << "t_3_bis : " << t_3_bis << std::endl; */

    double t_min_max = std::min({std::max(t_1, t_1_bis), std::max(t_2, t_2_bis), std::max(t_3, t_3_bis)});
    double t_max_min = std::max({std::min(t_1, t_1_bis), std::min(t_2, t_2_bis), std::min(t_3, t_3_bis)});

    /* std::cout << "min(t_max) : " << t_min_max << std::endl; */
    /* std::cout << "max(t_min) : " << t_max_min << std::endl; */

    if (t_min_max > t_max_min) {
        intersections.push_back(t_min_max);
        intersections.push_back(t_max_min);
        std::sort(intersections.begin(), intersections.end(), std::less<double>());
    }

    return intersections;
}

Vector* Cube::getNormal(const Ray rayon) const{
    std::vector<double> intersections = this->getIntersections(rayon);

    if (intersections.size() > 0) {
        double first_positive = help_fun::getFirstPositive(intersections);
        /* std::cout << "first_positive" << first_positive << std::endl; */

        for(auto const& plan: this->planes) {
            if (help_fun::double_equals(plan.getIntersections(rayon)[0], first_positive)) {
                return plan.getNormal(rayon);
            }
        }

    }

    return new Vector(0, 0, 0);
}

bool Cube::isInside(const Vector point) const{
    for(auto const& plan: this->planes) {
        if (!plan.isInside(point)) {
            return false;
        }
    }
    return true;
}

Ray Cube::getRandomRayToObject(Vector intersection) const{
    double x1 = distrib(engine);
    double x2 = distrib(engine);
    double x3 = distrib(engine);

    Vector point = this->point + x1*this->dir1 + x2*this->dir2 + x3*this->dir3;
    return Ray(intersection, point-intersection);
}

