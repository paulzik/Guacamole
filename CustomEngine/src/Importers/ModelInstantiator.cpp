#include "Importers/ModelInstantiator.h"
#include "Assets/Model.h"
#include <memory>
#include "ECS/MeshRenderer.h"

std::unique_ptr<Entity> ModelInstantiator::Instantiate(const std::shared_ptr<Asset>& asset,
    const char* entityName,
    const glm::vec3& position)
{
    std::shared_ptr<Model> model = std::dynamic_pointer_cast<Model>(asset);

    if (!model || model->meshes.empty()) {
        return nullptr;
    }

    auto entity = std::make_unique<Entity>(entityName, position);

    // --------- Only use the FIRST mesh ---------
    auto& mesh = model->meshes[0];

    // Attach components ONCE
    MeshFilter& filter = entity->AddComponent<MeshFilter>(*mesh);
    //MeshRenderer& renderer = entity->AddComponent<MeshRenderer>();

    //renderer.Start();

    return entity;
}
