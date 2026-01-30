#include "PhysicsSystem.h"
#include "ECS/Transform.h"
#include "ECS/Entity.h"
#include "Collider.h"
#include "glm/vec3.hpp"
#include "Time/Time.h"
#include "Utilities/Debug/Debug.h"
#include "Collider.h"

bool PhysicsSystem::Init() {
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    broadphase = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver();

    world = new btDiscreteDynamicsWorld(
        dispatcher,
        broadphase,
        solver,
        collisionConfiguration
    );

    world->setGravity(btVector3(0, -9.81f, 0));
    return true;
}

void PhysicsSystem::Update() {
    Step(Time::DeltaTime());
}

void PhysicsSystem::Step(float deltaTime) {
    if (!world) return;
    world->stepSimulation(deltaTime, 10);

    SyncTransforms();
}

void PhysicsSystem::SyncTransforms()
{
    for (int j = world->getNumCollisionObjects() - 1; j >= 0; j--)
    {
        btCollisionObject* obj = world->getCollisionObjectArray()[j];
        btRigidBody* btBody = btRigidBody::upcast(obj);
        if (!btBody) continue;

        btTransform btTrans;
        if (btBody->getMotionState())
            btBody->getMotionState()->getWorldTransform(btTrans);
        else
            btTrans = obj->getWorldTransform();

        RigidBody* myBody = static_cast<RigidBody*>(btBody->getUserPointer());
        if (!myBody) continue;

        Transform& transform = myBody->owner->GetComponent<Transform>();

        //Position
        glm::vec3 newPosition = glm::vec3(btTrans.getOrigin().getX(),
                                          btTrans.getOrigin().getY(),
                                          btTrans.getOrigin().getZ());
        transform.position = newPosition;

        //Rotation
        btQuaternion btRotation = btTrans.getRotation();
        
        glm::quat newRotation = glm::quat(btRotation.getW(),
                                          btRotation.getX(),
                                          btRotation.getY(), 
                                          btRotation.getZ());

        transform.rotation = newRotation;
    }
}

void PhysicsSystem::RegisterBody(RigidBody* body)
{
    //Get the Collider shape from the component here
    Collider& collider = body->owner->GetComponent<Collider>();

    btCollisionShape* colShape = CreateBulletShape(collider.colliderDescriptor);
    collisionShapes.push_back(colShape);

    /// Create Dynamic Objects
    btTransform startTransform;
    startTransform.setIdentity();

    Transform& transform = body->owner->GetComponent<Transform>();
    glm::vec3 globalPosition = transform.position;
    startTransform.setOrigin(btVector3(globalPosition.x, globalPosition.y, globalPosition.z));

    btScalar mass(body->mass);

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        colShape->calculateLocalInertia(mass, localInertia);


    //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
    btRigidBody* btBody = new btRigidBody(rbInfo);

    btBody->setUserPointer(body);

    world->addRigidBody(btBody);

    body->m_InternalBody = btBody;

}

btCollisionShape* PhysicsSystem::CreateBulletShape(const ColliderDescription& desc) {
    switch (desc.type)
    {
    case ColliderType::Box:
        return new btBoxShape(btVector3(desc.halfExtend.x, desc.halfExtend.y, desc.halfExtend.z));
    case ColliderType::Sphere:
        return new btSphereShape(desc.radius);
    case ColliderType::Capsule:
        return new btCapsuleShape(desc.radius, desc.height);
    case ColliderType::Mesh:
        Debug::LogError("MeshCollider not yet implemented");
        return nullptr;
    default:
        return nullptr;
    }
}

void PhysicsSystem::RemoveBody(RigidBody* body)
{
    if (!body || !body->m_InternalBody)
        return;
    btRigidBody* btBody = static_cast<btRigidBody*>(body->m_InternalBody);

    world->removeRigidBody(btBody);

    delete btBody->getMotionState();
    delete btBody;

    body->m_InternalBody = nullptr;
}

void PhysicsSystem::Shutdown()
{
    if (!world) return;

    // 1. Remove and delete rigid bodies
    for (int i = 0; i < world->getNonStaticRigidBodies().size(); ++i)
    {
        btRigidBody* body = world->getNonStaticRigidBodies()[i];
        world->removeRigidBody(body);

        delete body->getMotionState();
        delete body;
    }
    world->getNonStaticRigidBodies().clear();

    // 2. Delete collision shapes
    for (int i = 0; i < collisionShapes.size(); ++i)
    {
        delete collisionShapes[i];
    }

    collisionShapes.clear();

    delete world;
    world = nullptr;

    delete solver;
    delete broadphase;
    delete dispatcher;
    delete collisionConfiguration;

    solver = nullptr;
    broadphase = nullptr;
    dispatcher = nullptr;
    collisionConfiguration = nullptr;
}