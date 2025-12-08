#pragma once
#include "Material.h"
#include "ModelImporter/Asset.h"
#include "glm/vec4.hpp"

class Material : public Asset
{
public:
    //Texture2D* albedo = nullptr;
    //Texture2D* normal = nullptr;
    glm::vec4 baseColor = { 1,1,1,1 };

    //Shader* shader = nullptr;

    virtual ~Material() = default;
};