#pragma once
#include <vector>
#include "Entity.h"
#include "ECS/Camera.h"

class Scene {
private:
	std::vector<Entity*> scenegraph;

	Camera* sceneCamera;

public:
	Scene();
	~Scene();

	static Scene& Get();

	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);
	void PrintEntities();

	Camera* getCamera();
	void AddCamera(Camera* camera);
};