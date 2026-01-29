#pragma once
#include "ECS/Component.h"
#include "Assets/Material.h"
#include "Assets/Shader.h"
#include <memory>

class MeshRenderer : public Component {
public:
    std::shared_ptr<Material> material = nullptr;
    bool wireframe = false;

    MeshRenderer();
    ~MeshRenderer();

    void Start() override;
    void Update() override;

    const char* GetComponentName() const override;

};
