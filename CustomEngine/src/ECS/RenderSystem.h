#pragma once
#include "Systems/System.h"
#include "ECS/MeshRenderer.h"
#include "ECS/SkinnedMeshRenderer.h"


class RenderSystem : public System {
    void TryRegister(Component* c) override;
    bool Init() override;
    void Update() override;
    void Shutdown() override;

private:
    std::vector<MeshRenderer*> meshRenderers;
    std::vector<SkinnedMeshRenderer*> skinnedRenderers;

    void UpdateMeshRenderers(MeshRenderer* meshRenderer);
};