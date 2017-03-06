#include "Scene.h"

Scene::Scene(){

}

Scene::~Scene(){

}

std::vector<Object*> Scene::getObjects() const{
    return objects;
}

void Scene::addObject(Object* object){
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

Object* Scene::getCurrentObject(Vector position)
{
    Object* object = 0;
    double min_distance = -1;

    for(int i = 0; i < static_cast<int>( objects.size() ); i++) {
        if (objects[i]->isInside(position)) {
            double distance_to_center = (position - objects[i]->getCenter()).norm();
            if (min_distance == -1 || distance_to_center < min_distance) {
                min_distance = distance_to_center;
                object = objects[i];
            }
        }
    }

    return object;
}


/* void Scene::addSphere(const Sphere sphere){ */
/*     objects.push_back(sphere); */
/* } */

/* /1* get the first sphere that the ray crosses */
/*  * if there is no, return a sphere with a radius of 0 *1/ */
/* Sphere Scene::getSphere(Ray ray){ */
/*     Sphere first_sphere = Sphere(Vector(0, 0, 0), 0, Vector(1, 1, 1), 0, 0, 1); */
/*     double tMin = -1; */
/*     for(int i = 0; i < static_cast<int>( objects.size() ); i++) { */
/*         double t = ray.getDistanceToSphere(objects[i]); */
/*         if (t > -1 && (t < tMin || tMin < 0)) { */
/*             tMin = t; */
/*             first_sphere = objects[i]; */
/*         } */
/*     } */
/*     return first_sphere; */
/* } */
