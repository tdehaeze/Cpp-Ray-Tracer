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

Inter* Scene::getInter(Ray rayon, double indice) const{
    Object* closest_object = 0;
    double t_min = -1;

    for(auto const& object: this->getObjects()) {
        if (DEBUG) std::cout << "predistance" << std::endl;
        double t = object->getDistance(rayon);
        if (DEBUG) std::cout << "distance : " << t << std::endl;
        if (t > 0 && ( t < t_min || t_min < 0 )) {
            closest_object = object;
            t_min = t;
        }
    }

    Inter* inter = new Inter(closest_object, rayon, t_min, indice);

    return inter;
}

/* Vector* Scene::getIntersect(Ray rayon) const{ */
/*     Object* closest_object = this->getIntersectedObject(rayon); */
/*     if (closest_object == 0) { */
/*         return 0; */
/*     } else { */
/*         return closest_object->getIntersect(rayon); */
/*     } */
/* } */

/* Vector* Scene::getNormal(Ray rayon) const{ */
/*     Object* closest_object = this->getIntersectedObject(rayon); */
/*     if (closest_object == 0) { */
/*         return 0; */
/*     } else { */
/*         return closest_object->getNormal(rayon); */
/*     } */
/* } */

