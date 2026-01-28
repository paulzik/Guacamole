#pragma once
#include "System.h"
#include <vector>
#include <memory>

class SystemManager{
public:

	static SystemManager& GetInstance() {
		static SystemManager instance;
		return instance;
	}

	static void AddSystem(std::unique_ptr<System> system);
	
	template<typename T>
	void RemoveSystem()
	{
		systems.erase(
			std::remove_if(systems.begin(), systems.end(),
				[](const std::unique_ptr<System>& s) {
					return dynamic_cast<T*>(s.get()) != nullptr;
				}),
			systems.end()
		);
	}

	template<typename T>
	static T& Get() {
		static_assert(std::is_base_of<System, T>::value, "T must inherit from System");

		for (auto& sys : GetInstance().systems) {
			if (auto ptr = dynamic_cast<T*>(sys.get()))
				return *ptr;
		}
		//FIXXX
		//std::cout << "System not found" << std::endl;
		//throw std::runtime_error("System not found");
	}

	void ShutdownSystem(System* system);
	static void ShutdownAllSystems();

	static void UpdateAllSystems();

private:
	static inline std::vector<std::unique_ptr<System>> systems;
};