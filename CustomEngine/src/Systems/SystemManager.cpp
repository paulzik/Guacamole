#include "SystemManager.h"

void SystemManager::AddSystem(std::unique_ptr<System> system)
{
    system->Init();
    systems.push_back(std::move(system));
}

void SystemManager::UpdateAllSystems()
{
    for (auto& s : systems)
        s->Update();
}

void SystemManager::ShutdownAllSystems()
{
    for (auto& s : systems)
        s->Shutdown();

    systems.clear();
}
void SystemManager::ShutdownSystem(System* system)
{
    systems.erase(
        std::remove_if(
            systems.begin(), systems.end(),
            [system](std::unique_ptr<System>& s)
            {
                if (s.get() == system)
                {
                    s->Shutdown();
                    return true;
                }
                return false;
            }),
        systems.end()
    );
}
