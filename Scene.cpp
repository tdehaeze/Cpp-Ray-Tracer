#include "Scene.h"

Scene::Scene(){

}

Scene::~Scene(){

}

std::vector<Object*> Scene::getObjects() const{
    return objects;
}

void Scene::addSphere(Object* object){
    objects.push_back(object);
}

Object* Scene::getIntersectedObject(Ray rayon) const{
    Object* closest_object = 0;
    double t_min = -1;

    for(int i = 0; i < static_cast<int>( objects.size() ); i++) {
        double t = objects[i]->getDistance(rayon);
        if (t > -1 && (t < t_min || t_min < 0)) {
            closest_object = objects[i];
            t_min = t;
        }
    }

    return closest_object;
}

Vector* Scene::getIntersect(Ray rayon) const{
    Object* closest_object = getIntersectedObject(rayon);
    if (closest_object == 0) {
        return 0;
    } else {
        return closest_object->getIntersect(rayon);
    }
}

Vector* Scene::getNormal(Ray rayon) const{
    Object* closest_object = getIntersectedObject(rayon);
    if (closest_object == 0) {
        return 0;
    } else {
        return closest_object->getNormal(rayon);
    }
}

/* void Scene::addSphere(const Sphere sphere){ */
/*     spheres.push_back(sphere); */
/* } */

/* /1* get the first sphere that the ray crosses */
/*  * if there is no, return a sphere with a radius of 0 *1/ */
/* Sphere Scene::getSphere(Ray ray){ */
/*     Sphere first_sphere = Sphere(Vector(0, 0, 0), 0, Vector(1, 1, 1), 0, 0, 1); */
/*     double tMin = -1; */
/*     for(int i = 0; i < static_cast<int>( spheres.size() ); i++) { */
/*         double t = ray.getDistanceToSphere(spheres[i]); */
/*         if (t > -1 && (t < tMin || tMin < 0)) { */
/*             tMin = t; */
/*             first_sphere = spheres[i]; */
/*         } */
/*     } */
/*     return first_sphere; */
/* } */

/* Sphere Scene::getCurrentSphere(Vector position) */
/* { */
/*     Sphere sphere = Sphere(Vector(0, 0, 0), 0, Vector(1, 1, 1), 0, 0, 1); */

/*     double min_radius = -1; */

/*     for(int i = 0; i < static_cast<int>( spheres.size() ); i++) { */
/*         double distance_to_center = (position - spheres[i].origin).norm(); */
/*         if (distance_to_center < spheres[i].radius) { /1* we are inside the sphere *1/ */
/*             if (min_radius == -1 || spheres[i].radius < min_radius) */
/*                 sphere = spheres[i]; */
/*         } */
/*     } */

/*     return sphere; */
/* } */
