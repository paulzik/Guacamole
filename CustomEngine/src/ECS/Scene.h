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
	friend class SceneSerializer;
private:
	Scenegraph scenegraph;
	std::vector<std::unique_ptr<Entity>> entities;

	Camera* sceneCamera = nullptr;
	std::vector<Light*> lights;

	Entity* CreateEntity(const std::string& name, glm::vec3 position, Entity* parent, uint64_t entityID);


public:
	Scene();
	~Scene();

	static Scene& Get();

	Entity* CreateEntity(const std::string& name, glm::vec3 position, Entity* parent = nullptr);

	void DeleteEntity(Entity* entity);
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