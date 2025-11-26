#pragma once
#include <vector>
#include "Entity.h"
#include "ECS/Camera.h"
#include "Lighting/Light.h"
#include "Scenegraph/Scenegraph.h"

class Scene {
private:
	Scenegraph scenegraph;

	Camera* sceneCamera;
	std::vector<Light*> lights;

public:
	Scene();
	~Scene();

	static Scene& Get();

	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);
	void PrintEntities();

	Camera* getCamera();
	void AddCamera(Camera* camera);

	void AddLight(Light* light);
	std::vector<Light*> getLights();
};