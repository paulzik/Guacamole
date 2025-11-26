#pragma once
#include <vector>
#include <ECS/Entity.h>

class Scenegraph {
private:
	std::vector<Entity*> scenegraph;

public:
	Scenegraph();
	~Scenegraph();

	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);
	void PrintEntities();
};