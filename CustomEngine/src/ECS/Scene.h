#pragma once
#include <vector>
#include "Entity.h"
#include "ECS/Camera.h"
#include "Lighting/Light.h"
#include "Scenegraph/Scenegraph.h"

class Scene {
private:
	Scenegraph scenegraph;
	std::vector<Entity*> entities;

	Camera* sceneCamera;
	std::vector<Light*> lights;

	std::vector<Entity*> m_RenderableEntities;

public:
	Scene();
	~Scene();

	static Scene& Get();

	void AddEntity(Entity* entity, Entity* parent);
	void RemoveEntity(Entity* entity);
	void PrintEntities();

	Camera* GetCamera();
	void AddCamera(Camera* camera);

	void AddLight(Light* light);
	std::vector<Light*> GetLights();

	std::vector<Entity*>& GetRenderableEntities();
	void AddRenderableEntity(Entity* entity);
	void RemoveRenderableEntity(Entity* entity);

	void Update();
	void Start();

	Scenegraph& GetScenegraph();
};