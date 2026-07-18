#include "Importers/ModelInstantiator.h"
#include "Assets/Model.h"
#include <memory>
#include <string>
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
    entity->AddComponent<MeshFilter>(*model->meshes[0]);

    //Extra meshes become child entities so the whole model is visible.
    //They share the root position because transforms are not hierarchical yet.
    for (size_t i = 1; i < model->meshes.size(); ++i)
    {
        std::string childName = std::string(entityName) + "_Mesh" + std::to_string(i);
        Entity* child = new Entity(_strdup(childName.c_str()), position, entity.get());
        child->AddComponent<MeshFilter>(*model->meshes[i]);
    }

    return entity;
}
