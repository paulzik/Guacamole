#pragma once
#include <unordered_map>
#include <typeindex>
#include <functional>
#include "ComponentEditor/ComponentEditor.h"
#include "ECS/Component.h"

class EditorRegistry {
public:
    using EditorFactory = std::function<ComponentEditor* ()>;

    static EditorRegistry& Instance() {
        static EditorRegistry instance;
        return instance;
    }

    template<typename ComponentT, typename EditorT>
    void Register() {
        registry[typeid(ComponentT)] = []() -> ComponentEditor* {
            return new EditorT();
            };
    }

    ComponentEditor* CreateEditorFor(Component* component) {
        auto it = registry.find(typeid(*component));
        if (it == registry.end())
            return nullptr;

        return it->second(); // Create editor instance
    }

private:
    std::unordered_map<std::type_index, EditorFactory> registry;
};
