#pragma once
#include "Component.h"
#include <glm/vec3.hpp>
#include <list>
#include <vector>
#include <memory>
#include <stdexcept>
#include <iostream>
#include "Systems/SystemManager.h"
#include <unordered_map>
#include <typeindex>

class Entity {

private:
    std::vector<std::unique_ptr<Component>> components;
    int EntityID;
    const char* name;
    Entity* parent = nullptr;
    std::vector<Entity*> children;

public:
    Entity(const char* name, glm::vec3 entityPosition, Entity* parent);
    Entity(const char* name, glm::vec3 entityPosition);
    ~Entity();

    const char* GetName();
    void PrintComponents();

    void Update();
    void Start();

    void SetParent(Entity* parent);
    Entity* GetParent();

    std::vector<Entity*> GetChildren();
    void AddChild(Entity* child);
    void RemoveChild(Entity* child);

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

    //Gets the first component of type T it gets in the components
    template<typename T>
    T& GetComponent() {
        for (auto& c : components) {
            if (auto ptr = dynamic_cast<T*>(c.get()))
                return *ptr; // returns lvalue
        }
        std::cout << "Component " << typeid(T).name()<< " not found in entity " << GetName() << std::endl;
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