#include "Scene.h"
#include <iostream>

Scene& Scene::Get()
{
	static Scene instance;
	return instance;
}

Scene::Scene() {

}

Scene::~Scene() {

}

void Scene::AddEntity(Entity* entity)
{
	scenegraph.push_back(entity);
}

void Scene::RemoveEntity(Entity* entity) {
	scenegraph.erase(
		std::remove(scenegraph.begin(), scenegraph.end(), entity),
		scenegraph.end()
	);
}

void Scene::PrintEntities() {
	for (Entity* e : scenegraph) {
		std::cout << e->GetName() << std::endl;
	}
}
