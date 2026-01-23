#pragma once
#include "ECS/Component.h"
#include "Assets/Material.h"
#include "Assets/Shader.h"
#include <memory>

class MeshRenderer : public Component {
public:
    std::shared_ptr<Material> material = nullptr;

    MeshRenderer();
    ~MeshRenderer();

    void Draw(Shader* overrideShader = nullptr, unsigned int entityID = 0);

    void Start() override;
    void Update() override;

    const char* GetComponentName() const override;

private:

};
