#include "Scenegraph.h"
#include <iostream>

Scenegraph::Scenegraph() {

}

Scenegraph::~Scenegraph() {

}

void Scenegraph::AddEntity(Entity* entity, Entity* parent = nullptr)
{
	if (!entity) return;

	if (!parent) {
		entity->SetParent(nullptr);
		roots.push_back(entity);
	}
	else {
		Entity* actualParent = GetEntity(parent);
		if (!actualParent) {
			std::cout << "Parent of " << entity->GetName() << " not found\n";
			return;
		}
		entity->SetParent(actualParent);
		actualParent->AddChild(entity);
	}
}



Entity* Scenegraph::GetEntity(Entity* target)
{
	for (Entity* root : roots) {
		Entity* found = GetEntityRecursive(root, target);
		if (found) return found;
	}
	std::cout << "Entity " << target->GetName() << " not found" << std::endl;
	return nullptr;
}

Entity* Scenegraph::GetEntityRecursive(Entity* current, Entity* target)
{
	if (current == target)
		return current;

	for (Entity* child : current->GetChildren()) {
		Entity* found = GetEntityRecursive(child, target);
		if (found)
			return found;
	}

	return nullptr;
}


void Scenegraph::RemoveEntity(Entity* entity)
{
	roots.erase(
		std::remove(roots.begin(), roots.end(), entity),
		roots.end()
	);
}

void Scenegraph::PrintEntities()
{
	for (Entity* e : roots) {
		std::cout << e->GetName() << std::endl;
	}
}

std::vector<Entity*> Scenegraph::GetRoots()
{
	return roots;
}
