#include "Importers/ModelInstantiator.h"
#include "Assets/Model.h"
#include <memory>
#include <string>
#include "ECS/MeshRenderer.h"
#include "ECS/Scene.h"

Entity* ModelInstantiator::Instantiate(const std::shared_ptr<Asset>& asset,
    const std::string& entityName,
    const glm::vec3& position)
{
    std::shared_ptr<Model> model = std::dynamic_pointer_cast<Model>(asset);

    if (!model || model->meshes.empty()) {
        return nullptr;
    }

    Entity* entity = Scene::Get().CreateEntity(entityName, position);
    entity->AddComponent<MeshFilter>(*model->meshes[0]);

    for (size_t i = 1; i < model->meshes.size(); ++i)
    {
        std::string childName = entityName + "_Mesh" + std::to_string(i);
        Entity* child = Scene::Get().CreateEntity(childName, position, entity);
        child->AddComponent<MeshFilter>(*model->meshes[i]);
    }

    return entity;
}
