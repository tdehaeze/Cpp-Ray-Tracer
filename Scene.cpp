#include "Scene.h"

Scene::Scene(){

}

void Scene::addSphere(const Sphere sphere){
    spheres.push_back(sphere);
}

/* get the first sphere that the ray crosses
 * if there is no, return a sphere with a radius of 0 */
Sphere Scene::getSphere(Ray ray){
    Sphere first_sphere = Sphere(Vector(0, 0, 0), 0, Vector(1, 1, 1), 0, 0, 1);
    double tMin = -1;
    for(int i = 0; i < static_cast<int>( spheres.size() ); i++) {
        double t = ray.getDistanceToSphere(spheres[i]);
        if (t > -1 && (t < tMin || tMin < 0)) {
            tMin = t;
            first_sphere = spheres[i];
        }
    }
    return first_sphere;
}

Sphere Scene::getCurrentSphere(Vector position)
{
    Sphere sphere = Sphere(Vector(0, 0, 0), 0, Vector(1, 1, 1), 0, 0, 1);

    double min_radius = -1;

    for(int i = 0; i < static_cast<int>( spheres.size() ); i++) {
        double distance_to_center = (position - spheres[i].origin).norm();
        if (distance_to_center < spheres[i].radius) { /* we are inside the sphere */
            if (min_radius == -1 || spheres[i].radius < min_radius)
                sphere = spheres[i];
        }
    }

    return sphere;
}
