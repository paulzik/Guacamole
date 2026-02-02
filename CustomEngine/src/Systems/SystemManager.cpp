#include "SystemManager.h"
#include <ECS/MeshRenderer.h>
#include <ECS/SkinnedMeshRenderer.h>

void SystemManager::UpdateAllSystems()
{
    for (auto& [_, system] : systems)
        system->Update();
}

void SystemManager::ShutdownAllSystems()
{
    for (auto& [_,system] : systems)
        system->Shutdown();

    systems.clear();
}

void SystemManager::OnComponentAdded(Component* c)
{
    for (auto& [_, system] : systems)
        system->TryRegister(c);
}

void SystemManager::ShutdownSystem(System* system)
{
    auto it = std::find_if(
        systems.begin(), systems.end(),
        [system](auto& pair) { return pair.second.get() == system; }
    );

    if (it != systems.end())
    {
        it->second->Shutdown();
        systems.erase(it);
    }
}

void SystemManager::InitAllSystems()
{
    for (auto& [_, system] : systems)
        system->Init();
}