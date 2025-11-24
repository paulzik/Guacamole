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

Camera* Scene::getCamera()
{
	return sceneCamera;
}

void Scene::AddCamera(Camera* camera)
{
	sceneCamera = camera;
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
