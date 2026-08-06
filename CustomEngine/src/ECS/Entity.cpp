#include "Entity.h"
#include "Scene.h"
#include "Transform.h"
#include "ComponentFactory.h"
#include <iostream>
#include <random>

Entity::Entity(const std::string& _name, glm::vec3 entityPosition, Entity* parent)
    : name(_name)
{
    entityID = GenerateEntityID();

    auto transform = std::make_unique<Transform>();
    transform->position = entityPosition;
    components.push_back(std::move(transform));

}

Entity::Entity(const std::string& _name, glm::vec3 entityPosition)
    : name(_name)
{
    entityID = GenerateEntityID();

    auto transform = std::make_unique<Transform>();
    transform->position = entityPosition;
    components.push_back(std::move(transform));
}

Component& Entity::AttachComponent(std::unique_ptr<Component> component)
{
    component->owner = this;

    Component& ref = *component;
    components.push_back(std::move(component));

    SystemManager::OnComponentAdded(&ref);

    return ref;
}

Component* Entity::GetComponentByName(const std::string& name)
{
    for (auto& c : components)
    {
        if (name == c->GetComponentName())
            return c.get();
    }
    return nullptr;
}

Component* Entity::GetOrCreateComponent(const std::string& name)
{
    if (Component* existing = GetComponentByName(name))
        return existing;

    std::unique_ptr<Component> created = ComponentFactory::Instance().Create(name);
    if (!created)
        return nullptr; // unknown component type - caller decides what to do

    return &AttachComponent(std::move(created));
}

Entity::~Entity() {
    for (auto& component : components)
        SystemManager::OnComponentRemoved(component.get());
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
