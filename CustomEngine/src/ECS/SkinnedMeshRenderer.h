#pragma once
#include "ECS/Component.h"
#include "ECS/AssetReflection.h"
#include "Assets/Material.h"
#include "Assets/Shader.h"
#include <memory>

struct SkinnedMeshRenderer : public Component {
    std::shared_ptr<Material> material = nullptr;

    bool wireframe = false;

    COMPONENT_NAME(SkinnedMeshRenderer);

    void Reflect(IFieldVisitor& visitor) override
    {
        visitor.Visit("Wireframe", wireframe);

        std::string vertPath = (material && material->shader && material->shader->GetVertexShader())
            ? material->shader->GetVertexShader()->path : std::string();
        std::string fragPath = (material && material->shader && material->shader->GetFragmentShader())
            ? material->shader->GetFragmentShader()->path : std::string();

        visitor.Visit("VertexShader", vertPath);
        visitor.Visit("FragmentShader", fragPath);

        if (visitor.IsReading())
        {
            if (vertPath.empty() || fragPath.empty())
                return;

            if (!material)
                material = std::make_shared<Material>();
            material->shader = Shader::FromFiles(vertPath, fragPath);
        }
        else if (!material)
        {
            return;
        }

        VisitAssetRef(visitor, "Albedo", material->albedo);
        VisitAssetRef(visitor, "Normal", material->normal);
        visitor.Visit("BaseColor", material->baseColor);
        visitor.Visit("Metallic", material->metallic);
        visitor.Visit("Roughness", material->roughness);
    }
};
