#pragma once
#include "Systems/System.h"
#include <glm/vec3.hpp>
#include <vector>

struct MeshFilter;
class Entity;

class SelectionSystem : public System {
public:
    bool Init() override;
    void Update() override;
    void Shutdown() override;

    void TryRegister(Component* c) override;

    //Returns the closest entity under the given screen position, or nullptr
    Entity* Pick(float mouseX, float mouseY);

private:
    struct Pickable {
        MeshFilter* mesh;
        glm::vec3 localMin;
        glm::vec3 localMax;
    };

    std::vector<Pickable> pickables;
};
