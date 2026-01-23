#pragma once
#include "Component.h"
#include <glm/vec3.hpp>
#include <list>
#include <vector>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <Utilities/ObjectSelection.h>

class Entity {
private:
    std::vector<std::unique_ptr<Component>> components;
    EntityID entityID;
    const char* name;
    Entity* parent = nullptr;
    std::vector<Entity*> children;

public:
    Entity(const char* name, glm::vec3 entityPosition, Entity* parent);
    Entity(const char* name, glm::vec3 entityPosition);
    ~Entity();

    // Disable copying
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    // Enable moving
    Entity(Entity&&) noexcept = default;
    Entity& operator=(Entity&&) noexcept = default;

    const char* GetName();
    void PrintComponents();

    void Update();
    void Start();

    void SetParent(Entity* parent);
    Entity* GetParent();

    std::vector<Entity*> GetChildren();
    void AddChild(Entity* child);
    void RemoveChild(Entity* child);

    EntityID GetID() const;

    template<typename T, typename... Args>
    T& AddComponent(Args&&... args)
    {
        auto comp = std::make_unique<T>(std::forward<Args>(args)...);
        comp->setOwner(this); // set the owner pointer
        components.push_back(std::move(comp));
        return *static_cast<T*>(components.back().get());
    }

    template<typename T>
    T& GetComponent() {
        for (auto& c : components) {
            if (auto ptr = dynamic_cast<T*>(c.get()))
                return *ptr; // returns lvalue
        }
        std::cout << "Component " << typeid(T).name() << " not found in entity " << GetName() << std::endl;
        throw std::runtime_error("Component not found");
    }

    template<typename T>
    bool HasComponent() const
    {
        for (const auto& c : components)
        {
            if (dynamic_cast<T*>(c.get()))
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
