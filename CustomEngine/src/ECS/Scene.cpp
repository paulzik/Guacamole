#include "Scene.h"
#include <iostream>
#include "SelectedEntity.h"

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
	if (!entity) {
		std::cerr << "Entity to insert is null" << std::endl;
		return;
	}

	entities.push_back(entity);
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

std::vector<Light*> Scene::GetLights()
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
	if (!entity) {
		std::cerr << "Entity to remove is null" << std::endl;
		return;
	}

	// Remove from the linear vector
	auto it = std::find(entities.begin(), entities.end(), entity);
	if (it != entities.end()) {
		entities.erase(it);
	}
	else {
		std::cerr << "Entity not found in linear vector" << std::endl;
	}

	// Remove from the scenegraph
	scenegraph.RemoveEntity(entity);

	delete entity;
}

void Scene::Update() 
{
	for (Entity* e : entities)
	{
		e->Update();
	}
}

void Scene::Start() 
{
	for (Entity* e : entities)
	{
		e->Start();
	}
}


void Scene::PrintEntities() {
	scenegraph.PrintEntities();
}
