#pragma once
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "ECS/Component.h"
#include <glm/ext/matrix_transform.hpp>

class Camera : public Component {
private:
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

public:
    Camera(glm::vec3 lookAt);
    virtual ~Camera();

    const char* GetComponentName() const override;

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();

    void SetLookAtVector(glm::vec3 lookAt);
    void SetUpVector(glm::vec3 up);

    float GetFov();
    void SetFov(float fv);

    float GetNearPlane();
    void SetNearPlane(float np);

    float GetFarPlane();
    void SetFarPlane(float fp);

    glm::vec3 GetLookAt() const;
    void Update();

    void SetForward(glm::vec3 dir);
    void Move(glm::vec3 delta);
    glm::vec3 GetForwardFromRotation();

};
