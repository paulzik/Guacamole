#pragma once
#include "ECS/Component.h"
#include "ModelImporter/Material.h"
#include "ModelImporter/Shader.h"

class MeshRenderer : public Component {
public:
    Material* material = nullptr;
    Shader* shader = nullptr;

    MeshRenderer();
    ~MeshRenderer();

    void Start() override;
    void Update() override;

    const char* GetComponentName() const override;

private:

};
