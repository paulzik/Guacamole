#pragma once
#include <vector>
#include <memory>
#include "Asset.h"
#include "ECS/MeshFilter.h"

class Model : public Asset
{
public:
    std::vector<std::shared_ptr<MeshFilter>> meshes;

    Model() = default;
    explicit Model(const std::vector<std::shared_ptr<MeshFilter>>& _meshes)
        : meshes(_meshes)
    {
    }

    ~Model() override = default;
};