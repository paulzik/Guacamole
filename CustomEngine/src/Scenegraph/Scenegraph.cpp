#include "Scenegraph.h"
#include <iostream>

Scenegraph::Scenegraph() {

}

Scenegraph::~Scenegraph() {

}

void Scenegraph::AddEntity(Entity* entity)
{
	if (entity == nullptr) {
		std::cout << "Entity is null, cannot be added to the scenegraph" << std::endl;
	}

	scenegraph.push_back(entity);
}

void Scenegraph::RemoveEntity(Entity* entity) {
	scenegraph.erase(
		std::remove(scenegraph.begin(), scenegraph.end(), entity),
		scenegraph.end()
	);
}

void Scenegraph::PrintEntities() {
	for (Entity* e : scenegraph) {
		std::cout << e->GetName() << std::endl;
	}
}