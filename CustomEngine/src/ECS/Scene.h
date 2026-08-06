#pragma once
#include <vector>
#include "Entity.h"
#include "ECS/Camera/Camera.h"
#include "Lighting/Light.h"
#include "Scenegraph/Scenegraph.h"

enum AxisSystem
{
	Local, Global
};

class Scene {
private:
	Scenegraph scenegraph;
	std::vector<std::unique_ptr<Entity>> entities;

	Camera* sceneCamera = nullptr;
	std::vector<Light*> lights;

public:
	Scene();
	~Scene();

	static Scene& Get();

	// Creates an entity owned by the Scene and returns a non-owning pointer.
	Entity* CreateEntity(const std::string& name, glm::vec3 position, Entity* parent = nullptr);
	void RemoveEntity(Entity* entity);
	void PrintEntities();

	Camera* GetCamera();
	void AddCamera(Camera* camera);

	void AddLight(Light* light);
	std::vector<Light*> GetLights();

	const std::vector<std::unique_ptr<Entity>>& GetEntities() const;

	void Update();
	void Start();

	Scenegraph& GetScenegraph();
	Entity* selectedEntity = nullptr;
	AxisSystem axisSystem = Local;
};