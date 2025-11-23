#include "Entity.h"
#include "Scene.h"
#include "Transform.h"
#include <iostream>

Entity::Entity(const char* _name, glm::vec3 entityPosition)
    : name(_name)
{
    components.push_back(std::make_unique<Transform>(entityPosition));

    Scene::Get().AddEntity(this);
}

Entity::~Entity() {

}

const char* Entity::GetName() {
	return name;
}

void Entity::PrintComponents()
{
    for (const auto& c : components) {
        std::cout << c->GetComponentName() << std::endl;
    }
}
