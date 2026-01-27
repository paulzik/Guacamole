#pragma once
#include <btBulletDynamicsCommon.h>
#include "RigidBody.h"

class PhysicsSystem {
public:
    bool Init();
    void Shutdown();

    void Step(float dt);
    void SyncTransforms();

    void RegisterBody(RigidBody* body);
    void RemoveBody(RigidBody* body);

    btDiscreteDynamicsWorld* GetWorld() { return world; }

private:
    btDefaultCollisionConfiguration* collisionConfiguration = nullptr;
    btCollisionDispatcher* dispatcher = nullptr;
    btBroadphaseInterface* broadphase = nullptr;
    btSequentialImpulseConstraintSolver* solver = nullptr;
    btDiscreteDynamicsWorld* world = nullptr;

    btAlignedObjectArray<btCollisionShape*> collisionShapes;
};