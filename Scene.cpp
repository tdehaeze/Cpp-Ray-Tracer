#include "Scene.h"

Scene::Scene(){

}

void Scene::addSphere(const Sphere sphere){
    spheres.push_back(sphere);
}

/* get the first sphere that the ray crosses
 * if there is no, return a sphere with a radius of 0 */
Sphere Scene::getSphere(Ray ray){
    Sphere firstSphere = Sphere(Vector(0, 0, 0), 0, Vector(1, 1, 1));
    double tMin = -1;
    for(int i = 0; i < static_cast<int>( spheres.size() ); i++) {
        double t = ray.getDistanceToSphere(spheres[i]);
        if (t > -1 && (t < tMin || tMin < 0)) {
            tMin = t;
            firstSphere = spheres[i];
        }
    }
    return firstSphere;
}
