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

Entity* Scene::CreateEntity(const std::string& name, glm::vec3 position, Entity* parent)
{
	auto entity = std::make_unique<Entity>(name, position, parent);
	Entity* raw = entity.get();            

	entities.push_back(std::move(entity));
	scenegraph.AddEntity(raw, parent);

	return raw;
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

const std::vector<std::unique_ptr<Entity>>& Scene::GetEntities() const
{
	return entities;
}

Scenegraph& Scene::GetScenegraph()
{
	return scenegraph;
}

void Scene::DeleteEntity(Entity* entity) {
	if (!entity) {
		std::cerr << "Entity to delete is null" << std::endl;
		return;
	}

	for (Entity* child : entity->GetChildren())
		DeleteEntity(child);

	if (Entity* parent = entity->GetParent())
		parent->RemoveChild(entity);

	scenegraph.RemoveEntity(entity);

	if (selectedEntity == entity)
		selectedEntity = nullptr;

	for (Light* light : entity->GetComponents<Light>())
		std::erase(lights, light);

	if (sceneCamera && sceneCamera->owner == entity)
		sceneCamera = nullptr;

	auto it = std::find_if(entities.begin(), entities.end(),
		[entity](const std::unique_ptr<Entity>& e) { return e.get() == entity; });

	if (it != entities.end()) {
		entities.erase(it);
	}
	else {
		std::cerr << "Entity not found in linear vector" << std::endl;
	}
}

void Scene::Update() 
{
	for (const auto& e : entities) {
		e->Update();
	}
}

void Scene::Start() 
{
	for (const auto& e : entities) {
		e->Start();
	}
}


void Scene::PrintEntities() {
	scenegraph.PrintEntities();
}
