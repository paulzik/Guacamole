#pragma once
#include "ECS/Component.h"
#include "../Assets/Mesh.h"
#include <memory>


struct MeshFilter : public Component {
    std::shared_ptr<Mesh> mesh;

    MeshFilter() = default;
    explicit MeshFilter(std::shared_ptr<Mesh> mesh)
        : mesh(std::move(mesh)) {}

    COMPONENT_NAME(MeshFilter);

    void Reflect(IFieldVisitor& v) override {
        
        /* the mesh reference */ 
    
    }
};