#pragma once
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "ECS/Component.h"
#include <glm/ext/matrix_transform.hpp>

struct Camera : public Component {
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    //View Matrix data
    glm::vec3 lookAtVector = glm::vec3(0, 0, 0);
    glm::vec3 upVector = glm::vec3(0, 1, 0);
    glm::vec3 forward;

    //Projection Matrix data
    float fov = glm::radians(45.0f);
    float aspect = 16.0f / 9.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    COMPONENT_NAME(Camera);

    // viewMatrix/projectionMatrix and forward are rebuilt each frame by
    // CameraSystem, so only the inputs that produce them are persisted.
    void Reflect(IFieldVisitor& visitor) override
    {
        visitor.Visit("LookAt", lookAtVector);
        visitor.Visit("Up", upVector);
        visitor.Visit("Fov", fov);
        visitor.Visit("Aspect", aspect);
        visitor.Visit("NearPlane", nearPlane);
        visitor.Visit("FarPlane", farPlane);
    }
};