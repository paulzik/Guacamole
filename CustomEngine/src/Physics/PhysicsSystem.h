#pragma once
#include <btBulletDynamicsCommon.h>
#include "RigidBody.h"
#include "Systems/System.h"
#include <glm/vec3.hpp>
#include "Collider.h"

class PhysicsSystem : public System{
public:
    void TryRegister(Component* c) override;

    bool Init() override;
    void Update() override;
    void Shutdown() override;

    void Step(float dt);
    void SyncTransforms();

    void RegisterBody(RigidBody* body);
    void RemoveBody(RigidBody* body);

    btDiscreteDynamicsWorld* GetWorld() { return world; }
    btCollisionShape* CreateBulletShape(const ColliderDescription& desc);

private:
    btDefaultCollisionConfiguration* collisionConfiguration = nullptr;
    btCollisionDispatcher* dispatcher = nullptr;
    btBroadphaseInterface* broadphase = nullptr;
    btSequentialImpulseConstraintSolver* solver = nullptr;
    btDiscreteDynamicsWorld* world = nullptr;

    btAlignedObjectArray<btCollisionShape*> collisionShapes;
};