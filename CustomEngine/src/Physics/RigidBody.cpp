#include "RigidBody.h"
#include "PhysicsSystem.h"
#include "Systems/SystemManager.h"

void RigidBody::Start()
{
    PhysicsSystem& physics = SystemManager::Get<PhysicsSystem>();
    physics.RegisterBody(this);
}

void RigidBody::Update()
{
}

void RigidBody::Destroy()
{
}

void RigidBody::AddForce(const glm::vec3& force)
{

}

const char* RigidBody::GetComponentName() const
{
    return "RigidBody";
}