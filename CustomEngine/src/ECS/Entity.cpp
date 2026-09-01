#include "Entity.h"
#include "Transform.h"
#include "ComponentFactory.h"
#include <algorithm>
#include <iostream>
#include <random>

Entity::Entity(const std::string& name,glm::vec3 position,Entity* parent,uint64_t entityID)
    : name(name),parent(parent),entityID(entityID)
{
    auto transform = std::make_unique<Transform>();
    transform->position = position;
    components.push_back(std::move(transform));
}

Entity::Entity(const std::string& name,glm::vec3 position,Entity* parent)
    : Entity(name, position, parent, GenerateEntityID())
{}

Entity::Entity(const std::string& name,glm::vec3 position)
    : Entity(name, position, nullptr, GenerateEntityID())
{}

Component& Entity::AttachComponent(std::unique_ptr<Component> component)
{
    component->owner = this;

    Component& ref = *component;
    components.push_back(std::move(component));

    SystemManager::OnComponentAdded(&ref);

    return ref;
}

void Entity::RemoveComponent(Component* component)
{
    if (!component)
        return;

    auto it = std::find_if(components.begin(), components.end(),
        [component](const std::unique_ptr<Component>& c) { return c.get() == component; });

    if (it == components.end())
        return;

    SystemManager::OnComponentRemoved(component);
    components.erase(it);
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
        return;
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
