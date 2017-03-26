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
    if (object->getMaterial()->getEmissivity() > 0) {
        emissive_objects.push_back(object);
    }
}

std::vector<Object*> Scene::getEmissiveObjects() const{
    return this->emissive_objects;
}

Object* Scene::getRandomEmissiveObject() const{
	std::vector<Object*> emissive_objects = this->getEmissiveObjects();

	std::random_device random_device;
	std::mt19937 engine{random_device()};
	std::uniform_int_distribution<int> dist(0, emissive_objects.size() - 1);
	
	return emissive_objects[dist(engine)];
}

