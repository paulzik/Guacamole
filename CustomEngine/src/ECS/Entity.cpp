#include "Entity.h"
#include "Scene.h"
#include "Transform.h"
#include <iostream>
#include <random>

Entity::Entity(const char* _name, glm::vec3 entityPosition, Entity* parent)
    : name(_name)
{
    entityID = GenerateEntityID();

    auto transform = std::make_unique<Transform>(); // default constructor
    transform->position = entityPosition;          // assign manually
    components.push_back(std::move(transform));

    Scene::Get().AddEntity(this, parent);
}

Entity::Entity(const char* _name, glm::vec3 entityPosition)
    : name(_name)
{
    entityID = GenerateEntityID();

    auto transform = std::make_unique<Transform>(); // default constructor
    transform->position = entityPosition;          // assign manually
    components.push_back(std::move(transform));

    Scene::Get().AddEntity(this, nullptr);
}

Entity::~Entity() {

}

std::string Entity::GetName() {
	return name;
}

uint64_t Entity::GetEntityID() {
    return entityID;
}


uint64_t Entity::GenerateEntityID()
{
    static std::random_device rd;
    static std::mt19937_64 engine(rd());
    static std::uniform_int_distribution<uint64_t> dist(1, UINT64_MAX);

    return dist(engine);
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

void Entity::Start()
{
    for (auto& comp : components)
    {
        comp->Start();
    }
}
