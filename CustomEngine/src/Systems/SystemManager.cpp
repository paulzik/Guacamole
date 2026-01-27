#include "SystemManager.h"

void SystemManager::AddSystem(std::unique_ptr<System> system)
{
	systems.push_back(system);
}

void SystemManager::InitSystem(std::unique_ptr<System> system)
{
	if(system)
		system->Init();
}

void SystemManager::InitAllSystems()
{
	for (auto& s : systems) {
		s->Init();
	}
}

void SystemManager::ShutdownSystem(std::unique_ptr<System> system)
{
	//HEREEEEE!!!
}



