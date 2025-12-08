#pragma once
#include "Material.h"
#include "Assets/Asset.h"
#include "glm/vec4.hpp"
#include <memory>
#include "Shader.h"

class Material : public Asset
{
public:
    //Texture2D* albedo = nullptr;
    //Texture2D* normal = nullptr;
    glm::vec4 baseColor = { 1,1,1,1 };
    
    std::shared_ptr<Shader> shader = nullptr;

    Material(std::shared_ptr<Shader> s);
    virtual ~Material() = default;
};