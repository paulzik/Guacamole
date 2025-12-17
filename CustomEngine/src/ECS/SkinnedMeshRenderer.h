#pragma once
#include "ECS/Component.h"
#include "Assets/Material.h"
#include "Assets/Shader.h"
#include <memory>

class SkinnedMeshRenderer : public Component {
public:
    std::shared_ptr<Material> material = nullptr;

    SkinnedMeshRenderer();
    ~SkinnedMeshRenderer();

    void Start() override;
    void Update() override;

    const char* GetComponentName() const override;

private:

};
