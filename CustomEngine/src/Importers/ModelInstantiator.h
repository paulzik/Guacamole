#pragma once
#include <memory>
#include "ECS/Entity.h"
#include "Assets/Asset.h"

class ModelInstantiator
{
public:
    virtual ~ModelInstantiator() = default;

    static Entity* Instantiate(const std::shared_ptr<Asset>& asset,
                               const std::string& entityName,
                               const glm::vec3& position = glm::vec3(0));

};