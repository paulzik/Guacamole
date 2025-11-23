#pragma once
#include "Component.h"
#include <glm/vec3.hpp>
#include <list>
#include <vector>
#include <memory>

class Entity {

private:
    std::vector<std::unique_ptr<Component>> components;
    int EntityID;
    const char* name;

public:
    Entity(const char* name, glm::vec3 entityPosition);
    ~Entity();

    const char* GetName();
    void PrintComponents();

    template<typename T, typename... Args>
    T& AddComponent(Args&&... args)
    {
        components.push_back(
            std::make_unique<T>(std::forward<Args>(args)...)
        );

        return *static_cast<T*>(components.back().get());
    }

    //Gets the first component of type T it gets in the components
    template<typename T>
    T* GetComponent() {
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

        for (auto& c : components) {
            if(T* checkPointer =  dynamic_cast<T*>(c.get()))
                return checkedPointer;
        }

        return nullptr;
    }

    template<typename T>
    std::list<T*> GetComponents() {
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

        std::list<T*> componentsList;

        for (auto& c : components) {
            if (T* casted = dynamic_cast<T*>(c.get())) {
                componentsList.push_back(casted);
            }
        }

        return componentsList;
    }

};