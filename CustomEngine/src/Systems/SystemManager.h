#pragma once
#include "System.h"
#include "ECS/Component.h"
#include <vector>
#include <memory>
#include <typeindex>
#include <unordered_map>

class SystemManager{
public:

	static SystemManager& GetInstance() {
		static SystemManager instance;
		return instance;
	}

    template<typename T, typename... Args>
    static T& AddSystem(Args&&... args) {
        auto system = std::make_unique<T>(std::forward<Args>(args)...);
        T* ptr = system.get();
        systems[typeid(T)] = std::move(system);
        return *ptr;
    }

    template<typename T>
    static T* GetSystem()
    {
        auto it = systems.find(typeid(T));
        if (it != systems.end())
            return static_cast<T*>(it->second.get());
        return nullptr;
    }

	static void OnComponentAdded(Component* c);
	void ShutdownSystem(System* system);

	static void ShutdownAllSystems();
	static void UpdateAllSystems();
    static void InitAllSystems();
private:
	static inline std::unordered_map<std::type_index, std::unique_ptr<System>> systems;
};