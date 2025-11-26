#pragma once
#include <vector>
#include <ECS/Entity.h>

class Scenegraph {
private:
	std::vector<Entity*> roots;

public:
	Scenegraph();
	~Scenegraph();

	void AddEntity(Entity* entity, Entity* parent);
	void RemoveEntity(Entity* entity);
	Entity* GetEntity(Entity* target);
	Entity* GetEntityRecursive(Entity* current, Entity* target);

	void PrintEntities();

	std::vector<Entity*> GetRoots();
};