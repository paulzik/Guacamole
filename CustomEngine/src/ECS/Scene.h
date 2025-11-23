#pragma once
#include <vector>
#include "Entity.h"

class Scene {
private:
	std::vector<Entity*> scenegraph;

public:
	Scene();
	~Scene();

	static Scene& Get();

	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);
	void PrintEntities();
};