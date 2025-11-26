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

void Scene::AddEntity(Entity* entity, Entity* parent = nullptr)
{
	scenegraph.AddEntity(entity, parent);
}

Camera* Scene::GetCamera()
{
	return sceneCamera;
}

void Scene::AddCamera(Camera* camera)
{
	sceneCamera = camera;
}

void Scene::AddLight(Light* light)
{
	if (light == nullptr) {
		std::cout << "Null light added" << std::endl;
		return;
	}

	lights.push_back(light);
}

std::vector<Light*> Scene::getLights()
{
	if (lights.size() == 0) {
		std::cout << "No lights added" << std::endl;
	}
	return lights;
}

Scenegraph& Scene::GetScenegraph()
{
	return scenegraph;
}

void Scene::RemoveEntity(Entity* entity) {
	scenegraph.RemoveEntity(entity);
}

void Scene::PrintEntities() {
	scenegraph.PrintEntities();
}
