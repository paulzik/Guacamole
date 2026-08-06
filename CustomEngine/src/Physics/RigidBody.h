#pragma once
#include "ECS/Component.h"
#include <glm/fwd.hpp>


class RigidBody : public Component{
public:
    RigidBody(float m = 1.0f)
        : mass(m), friction(0.5f), restitution(0.0f),
        linearDamping(0.0f), angularDamping(0.0f),
        useGravity(true), isKinematic(false), m_InternalBody(nullptr) {
    }

    float mass;
    float friction;
    float restitution;
    float linearDamping;
    float angularDamping;
    bool useGravity;
    bool isKinematic;

    void Start() override;
    void Update() override;
    void Destroy() override;

    void AddForce(const glm::vec3& force);

    // Was a hand-written GetComponentName(); the macro yields the same string
    // ("RigidBody") and also provides StaticName(), which the scene loader's
    // ComponentFactory needs.
    COMPONENT_NAME(RigidBody);

    void Reflect(IFieldVisitor& visitor) override
    {
        visitor.Visit("Mass", mass);
        visitor.Visit("Friction", friction);
        visitor.Visit("Restitution", restitution);
        visitor.Visit("LinearDamping", linearDamping);
        visitor.Visit("AngularDamping", angularDamping);
        visitor.Visit("UseGravity", useGravity);
        visitor.Visit("IsKinematic", isKinematic);
    }

private:
    void* m_InternalBody;
    friend class PhysicsSystem;
};