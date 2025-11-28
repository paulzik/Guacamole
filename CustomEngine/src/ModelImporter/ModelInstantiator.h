#pragma once
#include <memory>
#include "ECS/Entity.h"
#include "ModelImporter/Asset.h"

class ModelInstantiator
{
public:
    virtual ~ModelInstantiator() = default;

    static std::unique_ptr<Entity> Instantiate(const std::shared_ptr<Asset>& asset,
                                               const char* entityName,
                                               const glm::vec3& position = glm::vec3(0));

};