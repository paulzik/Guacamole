#pragma once
#include "Material.h"
#include "Assets/Asset.h"
#include "glm/vec4.hpp"
#include <memory>
#include "Shader.h"
#include "Texture2D.h"

class Material : public Asset
{
public:
    std::shared_ptr<Shader> shader = nullptr;
    
    std::shared_ptr<Texture2D> albedo = nullptr;
    std::shared_ptr<Texture2D> normal = nullptr;

    glm::vec4 baseColor = { 1,1,1,1 };
    float metallic = 0.0f;
    float roughness = 1.0f;
    

    Material(std::shared_ptr<Shader> s);
    Material(std::shared_ptr<Texture2D> a, std::shared_ptr<Texture2D> n, std::shared_ptr<Shader> s);
    virtual ~Material() = default;
};