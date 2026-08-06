#pragma once
#include "Component.h"
#include <glm/vec3.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include "Systems/SystemManager.h"
#include <typeindex>
#include <stdexcept>
#include <string>

class Entity {

private:
    std::vector<std::unique_ptr<Component>> components;
    uint64_t entityID;
    std::string name;
    Entity* parent = nullptr;
    std::vector<Entity*> children;
    uint64_t GenerateEntityID();

public:
    Entity(const std::string& name, glm::vec3 entityPosition, Entity* parent);
    Entity(const std::string& name, glm::vec3 entityPosition);
    ~Entity();

    std::string GetName();
    void PrintComponents();

    void Update();
    void Start();

    void SetParent(Entity* parent);
    Entity* GetParent();

    std::vector<Entity*> GetChildren();
    void AddChild(Entity* child);
    void RemoveChild(Entity* child);

    uint64_t GetEntityID();

    const std::vector<std::unique_ptr<Component>>& GetAllComponents() const {
        return components;
    }


    Component& AttachComponent(std::unique_ptr<Component> component);
    Component* GetComponentByName(const std::string& name);
    Component* GetOrCreateComponent(const std::string& name);

    template<typename T, typename... Args>
    T& AddComponent(Args&&... args)
    {
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

        auto comp = std::make_unique<T>(std::forward<Args>(args)...);
        comp->owner = this;

        T& ref = *comp;
        components.push_back(std::move(comp));

        // Notify the system manager
        SystemManager::OnComponentAdded(&ref);

        return ref;
    }

    template<typename T>
    T& GetComponent() {
        for (auto& c : components) {
            if (auto ptr = dynamic_cast<T*>(c.get()))
                return *ptr; // returns lvalue
        }

        throw std::runtime_error(
            "Component " + std::string(typeid(T).name()) +
            " not found in entity " + GetName());
    }

    template<typename T>
    T* TryGetComponent()
    {
        for (auto& c : components)
        {
            if (auto ptr = dynamic_cast<T*>(c.get()))
                return ptr;
        }
        return nullptr;
    }

    template<typename T>
    bool HasComponent()
    {
        for (auto& c : components)
        {
            if (dynamic_cast<T*>(c.get()))
                return true;
        }
        return false;
    }

    bool HasComponent(std::type_index type)
    {
        for (auto& c : components)
        {
            if (std::type_index(typeid(*c)) == type)
                return true;
        }
        return false;
    }

    template<typename T>
    std::vector<T*> GetComponents() {
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

        std::vector<T*> componentsList;
        componentsList.reserve(components.size());

        for (auto& c : components) {
            if (T* casted = dynamic_cast<T*>(c.get())) {
                componentsList.push_back(casted);
            }
        }

        return componentsList;
    }

};