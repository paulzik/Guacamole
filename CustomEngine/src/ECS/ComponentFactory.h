#pragma once
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

struct Component;

class ComponentFactory {
public:
    using Creator = std::function<std::unique_ptr<Component>()>;

    static ComponentFactory& Instance();

    // Called from COMPONENT_NAME.
    template<typename T>
    static bool Register()
    {
        Instance().creators[T::StaticName()] = []() -> std::unique_ptr<Component> {
            return std::make_unique<T>();
        };
        return true;
    }

    // Returns a new component of that type
    std::unique_ptr<Component> Create(const std::string& name) const;

    bool IsRegistered(const std::string& name) const;

private:
    std::unordered_map<std::string, Creator> creators;
};
