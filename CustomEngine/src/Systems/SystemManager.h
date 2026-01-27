#pragma once
#include "System.h"
#include <vector>
#include <memory>

class SystemManager{
public:
	void AddSystem(std::unique_ptr<System> system);
	
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

	void ShutdownSystem(System* system);
	void ShutdownAllSystems();

	void UpdateAllSystems();

private:
	std::vector<std::unique_ptr<System>> systems;

	System* FindSystem(System* system);
};