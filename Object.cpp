#include "Object.h"

Object::Object(Material* m_material)
    : material(m_material) {}

Object::~Object(){

}

Material* Object::getMaterial() const{
    return material;
}

double Object::getDistance(const Ray rayon) const{
    std::vector<double> intersections = this->getIntersections(rayon);
    if (DEBUG) std::cout << "après get intersections" << std::endl;
    if (intersections.size() > 0) {
        return help_fun::getFirstPositive(intersections);
    } else {
        return -1;
    }
}

Vector* Object::getIntersect(Ray rayon) const{
    double t = this->getDistance(rayon);
    if (t > 0) {
        if (DEBUG) std::cout << "t" << t << std::endl;
        if (DEBUG) std::cout << "Origin of Ray : " << rayon.getOrigin() << std::endl;
        if (DEBUG) std::cout << "Direction of Ray : " << rayon.getDirection() << std::endl;
        Vector* intersect_point = new Vector(rayon.getOrigin() + t*rayon.getDirection());
        if (DEBUG) std::cout << "intersect_point" << *intersect_point << std::endl;
        return intersect_point;
    } else {
        return 0;
    }
}

