#pragma once
#include "ECS/Component.h"
#include "Assets/Material.h"
#include "Assets/Shader.h"
#include <memory>

struct MeshRenderer : public Component {
    std::shared_ptr<Material> material = nullptr;
    bool wireframe = false;

    COMPONENT_NAME(MeshRenderer);
};
