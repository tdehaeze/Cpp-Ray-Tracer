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

