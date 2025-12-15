#pragma once
#include <vector>
#include <memory>
#include "Asset.h"
#include "ECS/MeshFilter.h"
#include "Animations/Animation.h"
#include "Animations/Skeleton.h"

class Model : public Asset
{
public:
    std::vector<std::shared_ptr<MeshFilter>> meshes;
    std::shared_ptr<Skeleton> skeleton;
    std::vector<std::shared_ptr<Animation>> animations;

    Model() = default;
    Model(const std::vector<std::shared_ptr<MeshFilter>>& meshes,
        std::shared_ptr<Skeleton> skeleton,
        const std::vector<std::shared_ptr<Animation>>& animations)
        : meshes(meshes), skeleton(std::move(skeleton)), animations(animations) {
    }

    ~Model() override = default;
};