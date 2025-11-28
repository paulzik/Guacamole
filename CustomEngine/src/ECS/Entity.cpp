#include "Entity.h"
#include "Scene.h"
#include "Transform.h"
#include <iostream>

Entity::Entity(const char* _name, glm::vec3 entityPosition, Entity* parent)
    : name(_name)
{
    components.push_back(std::make_unique<Transform>(entityPosition));
    Scene::Get().AddEntity(this, parent);
}

Entity::Entity(const char* _name, glm::vec3 entityPosition)
    : name(_name)
{
    components.push_back(std::make_unique<Transform>(entityPosition));
    Scene::Get().AddEntity(this, nullptr);
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

void Entity::SetParent(Entity* _parent)
{
    parent = _parent;
}

Entity* Entity::GetParent()
{
    return parent;
}

std::vector<Entity*> Entity::GetChildren()
{
    return children;
}

void Entity::AddChild(Entity* child)
{
    if (!child) {
        std::cout << "Child is null abort" << std::endl;
    }

    children.push_back(child);
}

void Entity::RemoveChild(Entity* child)
{
    auto it = std::find(children.begin(), children.end(), child);

    if (it != children.end()) 
    {
        children.erase(it);

        if (child->GetParent() == this)
            child->SetParent(nullptr);
    }
}

void Entity::Update()
{
    for (auto& comp : components)
    {
        comp->Update();
    }
}
